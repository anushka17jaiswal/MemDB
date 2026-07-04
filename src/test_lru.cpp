#include "../include/LRUCache.h"

int main()
{
    LRUCache cache(3);

    cache.put("A");
    cache.put("B");
    cache.put("C");

    cache.printCache();

    cache.put("B");
    cache.printCache();

    cache.put("D");
    cache.printCache();

    return 0;
}