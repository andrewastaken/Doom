#include "WADLoader.h"
#include "WADReader.h"
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

void WADLoader::readDirectories() {
    WADReader reader;

    Header header;

    reader.readHeaderData(m_WADData, 0, header);

    std::cout << header.WADType << std::endl;
    std::cout << header.directoryCount << std::endl;
    std::cout << header.directoryOffset << std::endl;
    std::cout << std::endl << std::endl;

    Directory directory;

    for(int i = 0; i < header.directoryCount; i++) {
        reader.readDirectoryData(m_WADData, header.directoryOffset + i * 16, directory);

        m_WADDirectories.push_back(directory);

        std::cout << directory.lumpName << std::endl;
        std::cout << directory.lumpSize << std::endl;
        std::cout << directory.lumpOffset << std::endl;
        std::cout << std::endl;
    }    
}