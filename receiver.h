#ifndef RECEIVER
#define RECEIVER

#include <cstdint>

using namespace std;

struct status {
    uint64_t totalMessages = 0;
    uint64_t validMessages = 0;
    uint64_t invalidMessages = 0;
    uint64_t addOrderMessages = 0;
    uint64_t stockRelatedMessages = 0;
    uint64_t modifyMessages = 0;
    uint64_t tradeMessages = 0;
    uint64_t otherMessages = 0;
    uint64_t lastMessageNumber = 0;
};

#endif