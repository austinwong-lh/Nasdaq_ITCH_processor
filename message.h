#ifndef MESSAGE_ENCODER_DECODER
#define MESSAGE_ENCODER_DECODER

#include <array>
#include <cstdint>

struct message{
        char          orderType;
        std::uint16_t locate;
        std::uint16_t trackingNumber;
        std::uint64_t time;
        std::uint64_t referenceNumber;
        char          buySell;
        std::uint32_t shareNumber;
        char          stock[8];
        std::uint32_t price;
    };

message BinToMessage(std::array<std::uint8_t, 36> input);
std::array<std::uint8_t, 36> MessageToBin(message input);



#endif