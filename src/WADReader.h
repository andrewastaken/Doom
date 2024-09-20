#pragma once

#include "WADFile.h"
#include <string>
#include <fstream>
#include <cstdint>
#include <vector>

class WADReader {
    public:
        WADReader(std::string WADFilePath);
        
    private:
        std::string m_WADFilePath;
        std::ifstream m_WADFileStream;

        std::vector<uint8_t> m_WADFileBuffer; // the binary data of the file
        
        Header m_WADHeader;
        std::vector<Directory> m_WADDirectories;

        void loadWADFile();

        void readHeader();
        void readDirectories();

        template <typename T>
        std::vector<T> readBytes(size_t offset, unsigned int numBytes);
};