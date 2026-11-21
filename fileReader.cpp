#include <iostream>
#include <cstdint>
#include <array>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <cstring>
#include <zlib.h>
#include <thread>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {

    gzFile input = gzopen(argv[1], "rb");
    if (input == nullptr) {
        cout << "can't find file" << endl;
        return 1;
    }

    struct addrinfo hints, *servinfo;
    int rv;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // use AF_INET6 to force IPv6
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    rv = getaddrinfo("127.0.0.1", "8080", &hints, &servinfo);
    if (rv != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    int socketNumber = socket(servinfo -> ai_family, servinfo -> ai_socktype, servinfo -> ai_protocol);
    
    array<uint8_t,2> len = {0,0};
    uint8_t lenTemp = 0;
    uint8_t received = 0;
    uint8_t dataTemp = 0;
    uint16_t length = 0;
    vector<uint8_t> data = {};
    uint64_t messageNumber = 1;
    array<uint8_t, 8> message = {0,0,0,0,0,0,0,0};

    while (messageNumber < 500000){
        cout << "loop running" << endl;
        len = {0,0};
        data = {};

        
        for (int i = 7; i >= 0; i--) {
            message[i] = static_cast<uint8_t> (messageNumber >> 8*(i));
            data.push_back(message[i]);
        }
        cout << static_cast<uint64_t>(messageNumber) << endl;
        
        received = gzread(input,len.data(), 2);

        length = len[0] << 8 | len[1];

        cout << static_cast<int>(length) << endl;

        if (length == 0) {
            cout << "read 0 bytes of length " << endl;
            break;
        }
        
        for (int i = 0; i < length; i++) {
            data.push_back(0);
        }

        received = gzread(input, data.data() + message.size(), length);
        
        if (length == 0) {
            cout << "read 0 bytes of message" << endl;
            break;
        }

        ssize_t sent = sendto(socketNumber, data.data(), data.size(), 0, servinfo -> ai_addr, servinfo -> ai_addrlen);

        if (sent == -1) {
            cout << "send failed" <<endl;
            break;
        }

        this_thread::sleep_for(chrono::microseconds(60));

        messageNumber++;
    };

    freeaddrinfo(servinfo);
    cout << "finished program" << endl;
}