#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>

#define CACHE_SIZE 10

class LumpCache {
    public:
        std::vector<uint8_t> getLumpData(std::string lumpName);
        void putLumpData(std::string lumpName, std::vector<uint8_t> lumpData);

    private:
        std::list<std::pair<std::string, std::vector<uint8_t>>> m_usageOrderList;
        std::unordered_map<std::string, decltype(m_usageOrderList.begin())> m_lumpDataMap;
};  