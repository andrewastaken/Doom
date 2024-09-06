#pragma once

#include "WADFile.h"
#include <string>
#include <fstream>
#include <cstdint>
#include <vector>

class WADLoader {
    public:
        WADLoader(std::string WADFilePath);
        ~WADLoader();

        bool loadWADFile();
    
    private:
        std::string m_WADFilePath;
        std::ifstream m_WADFile;

        uint8_t *m_WADData;
        std::vector<Directory> m_WADDirectories;
};