#include "../include/LRUCache.h"
#include <iostream>
LRUCache::LRUCache(int cap)
{
    capacity = cap;
}
bool LRUCache::exists(const std::string &key)
{
    return cacheMap.find(key) != cacheMap.end();
}
std::optional<std::string> LRUCache::put(const std::string &key)

{
    if (exists(key))
    {
        cacheList.erase(cacheMap[key]);
    }
    cacheList.push_front(key);

cacheMap[key] = cacheList.begin();
if (cacheList.size() > capacity)
{
    std::string lruKey = cacheList.back();

    cacheMap.erase(lruKey);

    cacheList.pop_back();

    return lruKey;
}

return std::nullopt;
}
void LRUCache::printCache()
{
    std::cout << "Cache : ";

    for (const auto &key : cacheList)
    {
        std::cout << key << " ";
    }

    std::cout << std::endl;
}