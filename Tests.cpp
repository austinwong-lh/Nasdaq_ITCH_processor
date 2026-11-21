#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "message.h"
#include <string.h>

using namespace std;
TEST_CASE("Encode/Decode") {

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

    TEST_SUITE_BEGIN("Message to Binary");
    
        array<uint8_t, 36> resultBinary = static_cast<array<uint8_t, 36>>(MessageToBin(testMessage));
        for(int i = 0 ; i < 36 ; i++) {
            CHECK(resultBinary[i] == testBinary[i]);
        }
        message resultMessage = BinToMessage(testBinary);
        array<uint8_t, 36> resultBin = MessageToBin(resultMessage);
        for (int i = 0; i < 36; i++) {
        }
        CHECK(resultMessage.orderType == testMessage.orderType);
        CHECK(resultMessage.locate == testMessage.locate);
        CHECK(resultMessage.trackingNumber == testMessage.trackingNumber);
        CHECK(resultMessage.time == testMessage.time);
        CHECK(resultMessage.referenceNumber == testMessage.referenceNumber);
        CHECK(resultMessage.buySell == testMessage.buySell);
        CHECK(resultMessage.shareNumber == testMessage.shareNumber);
        for (int i = 0; i < 8; i++) {
            CHECK(resultMessage.stock[i] == testMessage.stock[i]);
        }
        CHECK(resultMessage.price == testMessage.price);


    TEST_SUITE_END;
}