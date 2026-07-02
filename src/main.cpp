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
    }

    std::cout << "Goodbye!" << std::endl;

    return 0;
}