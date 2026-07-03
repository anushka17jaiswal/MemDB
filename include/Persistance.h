#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <string>

class Persistence
{
public:
    static void save(const std::string &filename);
    static void load(const std::string &filename);
};

#endif