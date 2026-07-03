#include "../include/Database.h"
#include <fstream>
#include <sstream>
#include <iostream>
Database::Database()
{
}
void Database::set(const std::string &key, const std::string &value)
{
    store[key] = value;
}
void Database::set(const std::string &key, const std::string &value, int ttlSeconds)
{
    store[key] = value;
    expiry[key] = std::time(nullptr) + ttlSeconds;
}
std::string Database::get(const std::string &key) const
{
    auto it = store.find(key);

    if (it == store.end())
    {
        return "NULL";
    }

    auto exp = expiry.find(key);

    if (exp != expiry.end())
    {
        if (std::time(nullptr) > exp->second)
        {
            return "NULL";
        }
    }

    return it->second;
}
bool Database::exists(const std::string &key) const
{
    return store.find(key) != store.end();
}
bool Database::del(const std::string &key)
{
    return store.erase(key) > 0;
}
size_t Database::size() const
{
    return store.size();
}
void Database::clear()
{
    store.clear();
}
void Database::saveToFile(const std::string &filename) const
{
    std::ofstream file(filename);

    if (!file)
    {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    for (const auto &pair : store)
    {
        file << pair.first << "=" << pair.second << std::endl;
    }

    file.close();
}
void Database::loadFromFile(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file)
    {
        return;
    }

    store.clear();

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string key, value;

        if (std::getline(ss, key, '=') &&
            std::getline(ss, value))
        {
            store[key] = value;
        }
    }

    file.close();
}