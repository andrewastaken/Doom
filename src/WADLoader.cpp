#include "WADLoader.h"
#include <iostream>

WADLoader::WADLoader(std::string WADFilePath) {
    m_WADFilePath = WADFilePath;
    m_WADData = nullptr;
}

WADLoader::~WADLoader() {
    delete[] m_WADData;
    m_WADData = nullptr;
}

bool WADLoader::loadWADFile() {
    m_WADFile.open(m_WADFilePath, std::ifstream::binary);

    if(!m_WADFile.is_open()) {
        std::cout << "Error: could not open WAD file " << m_WADFilePath << std::endl;
        return false;
    }

    m_WADFile.seekg(0, m_WADFile.end);
    size_t fileLength = m_WADFile.tellg();
    m_WADFile.seekg(0, m_WADFile.beg);

    m_WADData = new uint8_t[fileLength];

    m_WADFile.read((char*) m_WADData, fileLength);
    m_WADFile.close();

    std::cout << "WAD file loading complete" << std::endl;
    return true;
}