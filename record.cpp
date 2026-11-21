#include <zlib.h>
#include "record.h"
#include <cstdint>
#include <vector>
#include <iostream>

using namespace std;

void record(const vector<uint8_t>& data, char file[]) {

    gzFile filePtr = gzopen(file, "ab" );

    uint8_t length = data.size() - 8;
    cout << length << endl;
    uint8_t length1 = 0;
    const vector<uint8_t>* start = reinterpret_cast<const uint8_t>(data.data());
    const vector<uint8_t>* start2 = start+8;

    gzwrite(filePtr, &(length1), 1);
    gzwrite(filePtr, &(length) , 1);

    gzwrite(filePtr, start, data.size());

    gzclose(filePtr);
}