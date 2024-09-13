#include "WADReader.h"
#include <iostream>
#include <cstring>

WADReader::WADReader() {
    m_WADFileData = nullptr;
}

WADReader::~WADReader() {
    delete[] m_WADFileData;
    m_WADFileData = nullptr;
}

void WADReader::setWADFilePath(std::string WADFilePath) {
    m_WADFilePath = WADFilePath;
}

bool WADReader::loadWADFile() {
    if(m_WADFilePath == "") {
        throw std::runtime_error("WAD file path not yet specified.");
    }

    m_WADFileStream.open(m_WADFilePath, std::ifstream::binary);

    if(!m_WADFileStream.is_open()) {
        throw std::runtime_error("Could not open WAD file.");
    }

    m_WADFileStream.seekg(0, m_WADFileStream.end);
    m_WADFileLength = m_WADFileStream.tellg();
    std::cout << m_WADFileLength << '\n';
    m_WADFileStream.seekg(0, m_WADFileStream.beg);

    m_WADFileData = new uint8_t[m_WADFileLength];

    m_WADFileStream.read((char*) m_WADFileData, m_WADFileLength);
    m_WADFileStream.close();

    std::cout << "WAD file loading complete." << std::endl;
    return true;
}

void WADReader::readHeader() {
    m_WADHeader.WADType = &readBytes<char>(0, 4)[0];
    m_WADHeader.lumpCount = readBytes<uint32_t>(4, 4)[0];
    m_WADHeader.initOffset = readBytes<uint32_t>(8, 4)[0];

    std::cout << "WAD type: " << m_WADHeader.WADType 
              << ", Lump count: " << m_WADHeader.lumpCount
              << ", Initial offset: " << m_WADHeader.initOffset
              << std::endl;
}

void WADReader::readDirectories() {
    for(int i = 0; i < m_WADHeader.lumpCount; i++) {
        size_t offset = m_WADHeader.initOffset + i * 16;

        Directory directory;
        directory.lumpOffset = readBytes<uint32_t>(offset + 0, 4)[0];
        directory.lumpSize = readBytes<uint32_t>(offset + 4, 4)[0];
        directory.lumpName = &readBytes<char>(offset + 8, 8)[0];

        m_WADDirectories.push_back(directory);

        std::cout << "Lump offset: " << directory.lumpOffset 
                  << ", Lump size: " << directory.lumpSize
                  << ", Lump name: " << directory.lumpName 
                  << std::endl;
    }

    
}

/**
 * This function reformats raw binary data into the specified type. The type parameter should be a C primitive type. 
 * 
 * @param WADFileData A pointer to the binary data that is being read from
 * @param initOffset The number of bytes to skip before reading
 * @param numBytes The number of bytes to read
 * 
 * @return A vector of the data in the specified byte format. It will always be a vector even if there is only one value in the vector.
 */
template <typename T>
std::vector<T> WADReader::readBytes(size_t initOffset, unsigned int numBytes) {
    if(!std::is_fundamental<T>::value) {
        throw std::invalid_argument("Specified type is not a primitive data type.");
    }
    
    if(numBytes % sizeof(T) != 0) {
        throw std::invalid_argument("Size of specified type is not evenly divisible by specified number of bytes.");
    }

    if(numBytes * sizeof(T) + initOffset > m_WADFileLength) {
        throw std::out_of_range("The specified parameters would result in reading out of bounds.");
    }

    std::vector<T> data;

    size_t offset = 0;

    while(sizeof(T) + offset <= numBytes) {
        T value;
        std::memcpy(&value, m_WADFileData + initOffset + offset, sizeof(T));
        data.push_back(value);
        offset += sizeof(T);
    }

    return data;
}