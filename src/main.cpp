#include <iostream>
#include <sstream>
#include "../include/Database.h"
#include "../include/Server.h"
int main()
{
    Database db;
Server server(db);

server.start();
    db.loadFromFile("data/database.db");

    std::string line;

    std::cout << "=====================================\n";
std::cout << "          MemDB v1.0\n";
std::cout << " Redis-inspired Key-Value Database\n";
std::cout << "=====================================\n";
std::cout << "Type HELP to see available commands.\n\n";

    while (true)
    {
        std::cout << "> ";

        std::getline(std::cin, line);

        if (line == "EXIT")
{
    db.saveToFile("data/database.db");
    std::cout << "Database saved successfully!" << std::endl;
    break;
}

        std::stringstream ss(line);

std::string command;

ss >> command;

if (command == "SET")
{
    std::string key, value;

    ss >> key >> value;

    std::string ex;
    int ttl;

    if (ss >> ex >> ttl)
    {
        if (ex == "EX")
        {
            db.set(key, value, ttl);
        }
        else
        {
            db.set(key, value);
        }
    }
    else
    {
        db.set(key, value);
    }

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
else if (command == "SAVE")
{
    db.saveToFile("data/database.db");
    std::cout << "Database saved successfully!" << std::endl;
}

else if (command == "LOAD")
{
    db.loadFromFile("data/database.db");
    std::cout << "Database loaded successfully!" << std::endl;
}
else if (command == "HELP")
{
    std::cout << "\nAvailable Commands\n";
    std::cout << "-------------------\n";
    std::cout << "SET <key> <value>\n";
    std::cout << "GET <key>\n";
    std::cout << "DEL <key>\n";
    std::cout << "EXISTS <key>\n";
    std::cout << "SIZE\n";
    std::cout << "CLEAR\n";
    std::cout << "SAVE\n";
    std::cout << "LOAD\n";
    std::cout << "HELP\n";
    std::cout << "EXIT\n";
}
else
{
    std::cout << "Unknown command. Type HELP." << std::endl;
}

    }

    std::cout << "Goodbye!" << std::endl;

    return 0;
}