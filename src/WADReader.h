#pragma once

#include "WADFile.h"
#include "LumpCache.h"

#include <string>
#include <fstream>
#include <cstdint>
#include <vector>

class WADReader {
    public:
        WADReader(std::string WADFilePath);
        
    private:
        std::string m_filePath;
        std::ifstream m_fileStream;

        std::vector<uint8_t> m_fileBuffer; // the binary data of the file
        
        Header m_header;

        std::vector<Directory> m_directories;

        LumpCache m_lumpCache;

        void loadWADFile();

        void readHeader();
        void readDirectories();

        template <typename T>
        std::vector<T> readBytes(size_t offset, int numBytes);
};