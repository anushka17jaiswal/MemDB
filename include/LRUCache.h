#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <string>
#include <list>
#include <unordered_map>
#include <optional>
class LRUCache
{
private:
    int capacity;

    std::list<std::string> cacheList;

    std::unordered_map<
        std::string,
        std::list<std::string>::iterator
    > cacheMap;

public:
    LRUCache(int cap);

    std::optional<std::string> put(const std::string &key);

    bool exists(const std::string &key);
    void printCache();
};

#endif