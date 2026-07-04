#ifndef SERVER_H
#define SERVER_H

#include "Database.h"

class Server
{
private:
    Database &db;

public:
    Server(Database &database);
    void start();
};

#endif