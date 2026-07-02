#include <iostream>
#include <sstream>
#include "../include/Database.h"

int main()
{
    Database db;

    std::string line;

    std::cout << "Welcome to MemDB!" << std::endl;

    while (true)
    {
        std::cout << "> ";

        std::getline(std::cin, line);

        if (line == "EXIT")
        {
            break;
        }

        std::stringstream ss(line);

std::string command;

ss >> command;

if (command == "SET")
{
    std::string key, value;

    ss >> key >> value;

    db.set(key, value);

    std::cout << "OK" << std::endl;
}
else if (command == "GET")
{
    std::string key;

    ss >> key;

    std::cout << db.get(key) << std::endl;
}
else if (command == "EXISTS")
{
    std::string key;

    ss >> key;

    if (db.exists(key))
    {
        std::cout << "TRUE" << std::endl;
    }
    else
    {
        std::cout << "FALSE" << std::endl;
    }
}
else if (command == "DEL")
{
    std::string key;

    ss >> key;

    if (db.del(key))
    {
        std::cout << "OK" << std::endl;
    }
    else
    {
        std::cout << "Key not found" << std::endl;
    }
}
else if (command == "SIZE")
{
    std::cout << db.size() << std::endl;
}
else if (command == "CLEAR")
{
    db.clear();

    std::cout << "OK" << std::endl;
}

    }

    std::cout << "Goodbye!" << std::endl;

    return 0;
}