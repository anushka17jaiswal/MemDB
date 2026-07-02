#include "../include/Database.h"

Database::Database()
{
}
void Database::set(const std::string &key, const std::string &value)
{
    store[key] = value;
}
std::string Database::get(const std::string &key) const
{
    auto it = store.find(key);

    if (it != store.end())
    {
        return it->second;
    }

    return "NULL";
}
bool Database::exists(const std::string &key) const
{
    return store.find(key) != store.end();
}
bool Database::del(const std::string &key)
{
    return store.erase(key) > 0;
}