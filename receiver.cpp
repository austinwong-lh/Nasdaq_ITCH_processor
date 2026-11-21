#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <cstring>
#include <cstdint>
#include <vector>
#include <iostream>
#include "receiver.h"
#include "processor.h"
#include "record.h"

using namespace std;

int main(int argc, char* argv[]) {

    struct addrinfo hints, *receiver;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // use AF_INET6 to force IPv6
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    int status = getaddrinfo("127.0.0.1", "8080", &hints, &receiver);
    if (status != 0) {
        cout << "address info error" << endl;
        return 1;
    }

    int socketNumber = socket(receiver -> ai_family, receiver -> ai_socktype, receiver -> ai_protocol);

    int binding = bind(socketNumber, receiver -> ai_addr, receiver -> ai_addrlen);

    if (binding ==-1) {
        cout << "binding failed" << endl;
        return 2;
    }

    vector<uint8_t> data = {};

    struct status info;

    memset(&info, 0, sizeof(info));

    struct status& total = info;

    while (true) {

        data = {};
        data.resize(64);

        uint16_t length = recvfrom(socketNumber, data.data(), data.size(), 0, nullptr, nullptr);

        if (length==0) {
            break;
        }

        vector<uint8_t>& dataRef = data;

        dataRef.resize(length);

        record(dataRef, argv[1]);

        processor(dataRef, total);


        cout << "add Order messages: "  << info.addOrderMessages << endl;
        cout << "other Messages: " << info.otherMessages << endl;
        cout << "valid messages: "  << info.validMessages << endl;
        cout << "modify messages: "  << info.modifyMessages << endl;
        cout << "stock Messages: " << info.stockRelatedMessages << endl;
        cout << "trade messages: "  << info.tradeMessages << endl;
        cout << "invalid Messages: " << info.invalidMessages << endl;
        cout << "total Messages: " << info.totalMessages << endl;
        cout << "\n" << endl;
        
    }
    freeaddrinfo(receiver);

}   