#ifndef MESSAGE_PROCESSOR
#define MESSAGE_PROCESSOR
#include "message.h"
#include "receiver.h"
#include <vector>

void processor(const vector<uint8_t>& data, status& info);

#endif