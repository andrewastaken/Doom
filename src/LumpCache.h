#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>

class LumpCache {
    public:
        std::vector<uint8_t>* getLumpData();
        void putLumpData(std::string lumpName, std::vector<uint8_t>* lumpData);

    private:
        size_t m_cacheSize;

        std::list<std::pair<std::string, std::vector<uint8_t>*>> m_usageOrderList;
        std::unordered_map<std::string, decltype(m_usageOrderList.begin())> m_lumpDataMap;
};