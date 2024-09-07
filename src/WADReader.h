#pragma once

#include "WADFile.h"
#include <cstdint>

class WADReader {
    public:
        void readHeaderData(uint8_t *pWADData, int offset, Header &header);
        void readDirectoryData(uint8_t *pWADData, int offset, Directory &directory);
        void readVertexData(uint8_t *pWADData, int offset, Vertex &vertex);
        void readLinedefData(uint8_t *pWADData, int offset, Linedef &linedef);
    
    private:
        char* readString(uint8_t *WADData, int offset);
        uint16_t read2Bytes(uint8_t *WADData, int offset);
        uint32_t read4Bytes(uint8_t *WADData, int offset);

        template <typename T>
        T readBytes(uint8_t *WADData, int offset);
};