#pragma once

#include <cstdint>

#define MAX_LUMP_NAME_LENGTH 9

struct Header {
    char WADType[4];
    uint32_t directoryCount;
    uint32_t directoryOffset;
};

struct Directory {
    char lumpName[MAX_LUMP_NAME_LENGTH];
    uint32_t lumpSize;
    uint32_t lumpOffset;
};

struct Vertex {

};

struct Linedef {
    
};