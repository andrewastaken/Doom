#pragma once

#include "WADFile.h"
#include <string>
#include <fstream>
#include <cstdint>
#include <vector>

class WADReader {
    public:
        WADReader();
        ~WADReader();

        void setWADFilePath(std::string WADFilePath);

        bool loadWADFile();

        void readHeader();
        void readDirectories();
    
    private:
        std::string m_WADFilePath;
        std::ifstream m_WADFileStream;

        uint8_t *m_WADFileData; // the binary data of the file
        size_t m_WADFileLength; // the number of bytes in the file

        Header m_WADHeader;
        std::vector<Directory> m_WADDirectories;

        template <typename T>
        std::vector<T> readBytes(size_t offset, unsigned int numBytes);
};