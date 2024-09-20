#pragma once

#include <cstdint>
#include <string>

struct Header {
    std::string WADType; // either IWAD or PWAD
    uint32_t lumpCount;
    uint32_t initOffset;
};

struct Directory {
    std::string lumpName;
    uint32_t lumpSize;  
    uint32_t lumpOffset;
};

struct Vertex {

};

struct Linedef {
    
};