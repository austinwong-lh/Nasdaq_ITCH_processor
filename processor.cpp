#include <cstdint>
#include "receiver.h"
#include "processor.h"
#include <iostream>
#include <vector>

using namespace std;


void processor(const vector<uint8_t>& data, status& info) {

    uint64_t messageNumber = 0;
    for(int i = 0; i < 8; i++) {
        messageNumber |= static_cast<std::uint64_t>(data[i]) << (8 * (7-i));
    }

    int length = data.size() - 8;

    uint64_t messageSkipped = messageNumber - info.lastMessageNumber;

    info.invalidMessages += messageSkipped - 1;
    info.totalMessages += messageSkipped - 1;

    switch (data[8]) {
    case 'A':
        // Length 36
        if (length == 36) {
            info.addOrderMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'F':
        // Length 40
        if (length == 40) {
            info.addOrderMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'S':
        // Length 12
        if (length == 12) {
            info.otherMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'R':
        // Length 39
        if (length == 39) {
            info.stockRelatedMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'H':
        // Length 25
        if (length == 25) {
            info.stockRelatedMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'Y':
        // Length 20
        if (length == 20) {
            info.stockRelatedMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'L':
        // Length 26
        if (length == 26) {
            info.stockRelatedMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'V':
        // Length 35
        if (length == 35) {
            info.stockRelatedMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'W':
        // Length 12
        if (length == 12) {
            info.stockRelatedMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'K':
        // Length 28
        if (length == 28) {
            info.stockRelatedMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'J':
        // Length 35
        if (length == 35) {
            info.stockRelatedMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'h':
        // Length 21
        if (length == 21) {
            info.stockRelatedMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'E':
        // Length 31
        if (length == 31) {
            info.modifyMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'C':
        // Length 36
        if (length == 36) {
            info.modifyMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'X':
        // Length 23
        if (length == 23) {
            info.modifyMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'D':
        // Length 19
        if (length == 19) {
            info.modifyMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'U':
        // Length 35
        if (length == 35) {
            info.modifyMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'P':
        // Length 44
        if (length == 44) {
            info.tradeMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'Q':
        // Length 40
        if (length == 40) {
            info.tradeMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'B':
        // Length 19
        if (length == 19) {
            info.tradeMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'I':
        // Length 50
        if (length == 50) {
            info.otherMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'N':
        // Length 20
        if (length == 20) {
            info.otherMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    case 'O':
        // Length 48
        if (length == 48) {
            info.otherMessages++;
            info.validMessages++;
        } else {
            info.invalidMessages++;
        }
        break;

    default:
        info.otherMessages++;
        info.invalidMessages++;
        break;
    }
    info.totalMessages++;
    info.lastMessageNumber = messageNumber;

}
