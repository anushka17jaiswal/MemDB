#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <unordered_map>
#include <ctime>

class Database
{
private:
    std::unordered_map<std::string, std::string> store;
    std::unordered_map<std::string, std::time_t> expiry;

public:
    Database();

    void set(const std::string &key, const std::string &value);
    void set(const std::string &key, const std::string &value, int ttlSeconds);

    std::string get(const std::string &key) const;

    bool del(const std::string &key);

    bool exists(const std::string &key) const;

    size_t size() const;
void saveToFile(const std::string &filename) const;

void loadFromFile(const std::string &filename);
    void clear();
};

#endif