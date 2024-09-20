#include "WADReader.h"
#include <iostream>
#include <cstring>

WADReader::WADReader(std::string WADFilePath) {
    m_WADFilePath = WADFilePath;

    loadWADFile();

    readHeader();
    readDirectories();
}

void WADReader::loadWADFile() {
    m_WADFileStream.open(m_WADFilePath, std::ifstream::binary);

    if(!m_WADFileStream.is_open()) {
        throw std::runtime_error("Could not open WAD file.");
    }

    m_WADFileStream.seekg(0, m_WADFileStream.end);
    size_t fileLength = m_WADFileStream.tellg();
    m_WADFileStream.seekg(0, m_WADFileStream.beg);

    m_WADFileBuffer.resize(fileLength);

    m_WADFileStream.read(reinterpret_cast<char*>(m_WADFileBuffer.data()), fileLength);

    m_WADFileStream.close();

    std::cout << "WAD file loading complete. " << m_WADFileBuffer.size() << " bytes read.\n";
}

void WADReader::readHeader() {
    auto WADNameVector = readBytes<char>(0, 4); 
    m_WADHeader.WADType = std::string(WADNameVector.data(), WADNameVector.size());

    m_WADHeader.lumpCount = readBytes<uint32_t>(4, 4)[0];
    m_WADHeader.initOffset = readBytes<uint32_t>(8, 4)[0];

    // std::cout << "WAD type: " << m_WADHeader.WADType << ", "
    //           << "Lump count: " << m_WADHeader.lumpCount << ", "
    //           << "Initial offset: " << m_WADHeader.initOffset << " bytes.\n";

    std::cout << "Header info read.\n";
              
}

void WADReader::readDirectories() {
    m_WADDirectories.reserve(m_WADHeader.lumpCount);

    for(int i = 0; i < m_WADHeader.lumpCount; i++) {
        size_t offset = m_WADHeader.initOffset + i * 16;

        Directory directory;
        directory.lumpOffset = readBytes<uint32_t>(offset, 4)[0];
        directory.lumpSize = readBytes<uint32_t>(offset + 4, 4)[0];

        auto lumpNameVector = readBytes<char>(offset + 8, 8);
        size_t lumpNameLength = strnlen(lumpNameVector.data(), lumpNameVector.size());
        directory.lumpName = std::string(lumpNameVector.data(), lumpNameLength);

        m_WADDirectories.push_back(directory);

        // std::cout << "Offset: " << offset << " bytes, "
        //           << "Distance from end of buffer: " << (m_WADFileBuffer.size() - offset) << " bytes, ";

        // std::cout << "Lump offset: " << directory.lumpOffset << " bytes, " 
        //           << "Lump size: " << directory.lumpSize << " bytes, "
        //           << "Lump name: " << directory.lumpName << "\n";
    }
    
    std::cout << "Directory info read.\n";
}

/**
 * This function reformats the raw binary data from the WAD file into the specified type. The type parameter should be a C primitive type. 
 * 
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

    if(numBytes + initOffset > m_WADFileBuffer.size()) {
        throw std::out_of_range("The specified parameters would result in reading out of bounds.");
    }

    std::vector<T> data;
    data.reserve(numBytes / sizeof(T));

    for(int i = 0; i < numBytes; i++) {
        size_t offset = initOffset + i * sizeof(T);

        T value;
        std::memcpy(&value, m_WADFileBuffer.data() + offset, sizeof(T));
        data.push_back(value);
    }
    
    return data;
}