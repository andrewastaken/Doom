#pragma once

#include <cstdint>

struct Header {
    char *WADType; // either IWAD or PWAD
    uint32_t lumpCount;
    uint32_t initOffset;
};

struct Directory {
    char* lumpName;
    uint32_t lumpSize;  
    uint32_t lumpOffset;
};

struct Vertex {

};

struct Linedef {
    
};