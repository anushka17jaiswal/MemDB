#ifndef SERVER_H
#define SERVER_H

#include "Database.h"
#include <mutex>
class Server
{

    private:
    Database &db;
    std::mutex dbMutex;

    void handleClient(int clientSocket);
    void sendResponse(int clientSocket, const std::string &response);
public:
    Server(Database &database);
    void start();
};

#endif