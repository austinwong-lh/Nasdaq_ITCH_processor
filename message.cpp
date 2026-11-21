#include "message.h"
#include <stdio.h>

using namespace std;

/*
int main (void) {
    message testMessage {
        .orderType = 'A', //1
        .locate = 16384, //2
        .trackingNumber = 16384, //2
        .time = 65536, //6
        .referenceNumber = 65536, //8
        .buySell = 'B', //1 
        .shareNumber = 32768, //4
        .stock = {'A','B','C','D','E','F','G','H'},
        .price=32768 //4
    };

    array<uint8_t, 36> testBinary = {
        65,
        64,0,
        64,0,
        0,0,0,1,0,0,
        0,0,0,0,0,1,0,0,
        66,
        0,0,128,0,
        65,66,67,68,69,70,71,72,
        0,0,128,0
    };
    
        message resultMessage = BinToMessage(testBinary);
        
        printf("%c %c\n", resultMessage.orderType, testMessage.orderType);
        printf("%d %d\n", resultMessage.locate, testMessage.locate);
        printf("%d %d\n", resultMessage.trackingNumber, testMessage.trackingNumber);
        printf("%llu %llu\n", resultMessage.time, testMessage.time);
        printf("%llu %llu\n", resultMessage.referenceNumber, testMessage.referenceNumber);
        printf("%c %c\n", resultMessage.buySell, testMessage.buySell);
        printf("%d %d\n", resultMessage.shareNumber, testMessage.shareNumber);
        for (int i = 0; i < 8; i++) {
            printf("%c", resultMessage.stock[i]);
        }
        printf("\n");
        printf("%d %d\n", resultMessage.price, testMessage.price);

        return 0;
}
*/


message BinToMessage(array<uint8_t, 36> input) {
    message output;
    output.orderType = static_cast<char>(input[0]);

    output.locate = static_cast<std::uint16_t>(input[1]<< 8 | input[2]);
    output.trackingNumber = static_cast<std::uint16_t>(input[3] << 8|input[4]);
    output.time = 0;
    for(int i = 0; i < 6; i++) {
        output.time |= static_cast<std::uint64_t>(input[i + 5]) << (8 * (5 - i));
    }
    output.referenceNumber = 0;
    for(int i = 0; i < 8; i++) {
        output.referenceNumber |= static_cast<std::uint64_t>(input[i + 11] << (8 * (7 - i)));
    }
    output.buySell = static_cast<char>(input[19]);
    output.shareNumber = 0;
    for(int i = 0; i < 4; i++) {
        output.shareNumber |= static_cast<std::uint32_t>(input[i + 20] << (8 * (3 - i)));
    }
    for(int i = 0; i < 8; i++) {
        output.stock[i] = static_cast<char>(input[24+i]);
    }
    output.price = 0;
    for(int i = 0; i < 4; i++) {
        output.price |= static_cast<std::uint32_t>(input[i + 32] << (8 * (3 - i)));
    }

    return output;
}

array<uint8_t, 36> MessageToBin(message input) {
    array<uint8_t, 36> binary;
    binary[0] = static_cast<uint8_t>(input.orderType);
    binary[1] = static_cast<uint8_t>(input.locate >> 8);
    binary[2] = static_cast<uint8_t>(input.locate);
    binary[3] = static_cast<uint8_t>(input.trackingNumber >> 8);
    binary[4] = static_cast<uint8_t>(input.trackingNumber);
    for (int i = 0; i < 6; i++) {
        binary[5+i] = static_cast<uint8_t>(input.time >> (8*(5-i)));
    }
    for (int i = 0; i < 8; i++) {
        binary[11+i] = static_cast<uint8_t>(input.referenceNumber >> (8*(7-i)));
    }
    binary[19] = static_cast<uint8_t>(input.buySell);
    for (int i = 0; i < 4; i++) {
        binary[20+i] = static_cast<uint8_t>(input.shareNumber >> (8*(3-i)));
    }    
    for (int i = 0; i < 8; i++) {
        binary[24+i] = static_cast<uint8_t>(input.stock[i]);
    }    
    for (int i = 0; i < 4; i++) {
        binary[32+i] = static_cast<uint8_t>(input.price >> (8*(3-i)));
    }
    
    return binary;
}