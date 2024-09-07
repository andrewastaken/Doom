#include "WADReader.h"
#include <cstring>

void WADReader::readHeaderData(uint8_t *WADData, int offset, Header &header) {
    header.WADType[0] = WADData[offset + 0];
    header.WADType[1] = WADData[offset + 1];
    header.WADType[2] = WADData[offset + 2];
    header.WADType[3] = WADData[offset + 3];
    header.WADType[4] = '\0';

    header.directoryCount = read4Bytes(WADData, offset + 4);

    header.directoryOffset = read4Bytes(WADData, offset + 8);
}

void WADReader::readDirectoryData(uint8_t *WADData, int offset, Directory &directory) {
    directory.lumpSize = read4Bytes(WADData, offset + 0);

    directory.lumpOffset = read4Bytes(WADData, offset + 4);

    directory.lumpName[0] = WADData[offset + 8];
    directory.lumpName[1] = WADData[offset + 9];
    directory.lumpName[2] = WADData[offset + 10];
    directory.lumpName[3] = WADData[offset + 11];
    directory.lumpName[4] = WADData[offset + 12];
    directory.lumpName[5] = WADData[offset + 13];
    directory.lumpName[6] = WADData[offset + 14];
    directory.lumpName[7] = WADData[offset + 15];
    directory.lumpName[8] = '\0';
}

void WADReader::readVertexData(uint8_t *WADData, int offset, Vertex &vertex) {

}
void WADReader::readLinedefData(uint8_t *WADData, int offset, Linedef &linedef) {

}

char* WADReader::readString(uint8_t *WADData, int offset) {
    return readBytes<char*>(WADData, offset);
}

uint16_t WADReader::read2Bytes(uint8_t *WADData, int offset) {
    return readBytes<uint16_t>(WADData, offset);
}

uint32_t WADReader::read4Bytes(uint8_t *WADData, int offset) {
    return readBytes<uint32_t>(WADData, offset);
}

template <typename T>
T WADReader::readBytes(uint8_t *WADData, int offset) {
    T data;
    std::memcpy(&data, WADData + offset, sizeof(T));
    return data;
}