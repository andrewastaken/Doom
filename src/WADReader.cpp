#include "WADReader.h"

#include <memory>
#include <bit>
#include <iostream>
#include <cstring>

WADReader::WADReader(std::string WADFilePath) {
    m_filePath = WADFilePath;

    loadWADFile();

    readHeader();
    readDirectories();
}

void WADReader::loadWADFile() {
    m_fileStream.open(m_filePath, std::ifstream::binary);

    if(!m_fileStream.is_open()) {
        throw std::runtime_error("Could not open WAD file.");
    }

    m_fileStream.seekg(0, m_fileStream.end);
    size_t fileLength = m_fileStream.tellg();
    m_fileStream.seekg(0, m_fileStream.beg);

    m_fileBuffer.resize(fileLength);

    if(!m_fileStream.read(std::bit_cast<char*>(m_fileBuffer.data()), fileLength)) {
        throw std::runtime_error("Failed to read WAD file.");
    }

    m_fileStream.close();

    std::cout << "WAD file loading complete. " << m_fileBuffer.size() << " bytes read.\n";
}

void WADReader::readHeader() {
    auto nameVector = readBytes<char>(0, 4); 
    m_header.WADType = std::string(nameVector.data(), nameVector.size());

    m_header.lumpCount = readBytes<uint32_t>(4, 4)[0];
    m_header.initOffset = readBytes<uint32_t>(8, 4)[0];

    // std::cout << "WAD type: " << m_header.WADType << ", "
    //           << "Lump count: " << m_header.lumpCount << ", "
    //           << "Initial offset: " << m_header.initOffset << " bytes.\n";

    std::cout << "Header info read.\n";
              
}

void WADReader::readDirectories() {
    m_directories.reserve(m_header.lumpCount);

    for(int i = 0; i < m_header.lumpCount; i++) {
        size_t offset = m_header.initOffset + i * 16;

        Directory directory;
        directory.lumpOffset = readBytes<uint32_t>(offset, 4)[0];
        directory.lumpSize = readBytes<uint32_t>(offset + 4, 4)[0];

        auto lumpNameVector = readBytes<char>(offset + 8, 8);
        size_t lumpNameLength = strnlen(lumpNameVector.data(), lumpNameVector.size());
        directory.lumpName = std::string(lumpNameVector.data(), lumpNameLength);

        m_directories.push_back(directory);

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
std::vector<T> WADReader::readBytes(size_t initOffset, int numBytes) {
    if(!std::is_fundamental<T>::value) {
        throw std::invalid_argument("Specified type is not a primitive data type.");
    }
    
    if(numBytes % sizeof(T) != 0) {
        throw std::invalid_argument("Size of specified type is not evenly divisible by specified number of bytes.");
    }

    if(numBytes + initOffset > m_fileBuffer.size()) {
        throw std::out_of_range("The specified parameters would result in reading out of bounds.");
    }

    std::vector<T> data;
    data.reserve(numBytes / sizeof(T));

    for(int i = 0; i < numBytes; i++) {
        size_t offset = initOffset + i * sizeof(T);

        T value;
        memcpy(&value, m_fileBuffer.data() + offset, sizeof(T));
        data.push_back(value);
    }
    
    return data;
}