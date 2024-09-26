#include "LumpCache.h"
#include <iostream>

std::vector<uint8_t> LumpCache::getLumpData(std::string lumpName) {
    auto it = m_lumpDataMap.find(lumpName);

    if(it == m_lumpDataMap.end()) {
        throw std::runtime_error("Could not find " + lumpName + " in cache.");
    }

    m_usageOrderList.splice(m_usageOrderList.begin(), m_usageOrderList, it->second);
    return it->second->second;
}

void LumpCache::putLumpData(std::string lumpName, std::vector<uint8_t> lumpData) {
    auto it = m_lumpDataMap.find(lumpName);

    if(it != m_lumpDataMap.end()) {
        m_usageOrderList.erase(it->second);
        m_lumpDataMap.erase(it);
    }

    m_usageOrderList.push_front(std::make_pair(lumpName, lumpData));
    m_lumpDataMap.insert(std::make_pair(lumpName, m_usageOrderList.begin()));

    if(m_lumpDataMap.size() > CACHE_SIZE) {
        m_lumpDataMap.erase(m_usageOrderList.end()->first);
        m_usageOrderList.pop_back();
    }
}