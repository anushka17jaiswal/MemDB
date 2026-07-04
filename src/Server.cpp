#include "../include/Server.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <cerrno>
#include <thread>
Server::Server(Database &database) : db(database)
{
}
void Server::sendResponse(int clientSocket,
                          const std::string &response)
{
    send(clientSocket,
         response.c_str(),
         response.length(),
         0);
}
void Server::handleClient(int clientSocket)
{
    std::cout << "Client connected successfully!" << std::endl;

    while (true)
    {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        int bytesReceived = recv(
            clientSocket,
            buffer,
            sizeof(buffer),
            0);

        if (bytesReceived <= 0)
        {
            break;
        }

        std::string message(buffer, bytesReceived);
        std::stringstream ss(message);

        std::string command;
        ss >> command;

        if (command == "PING")
{
    sendResponse(clientSocket, "PONG\n");
}
        else if (command == "SET")
        {
            std::string key, value;
            ss >> key >> value;

            {
    std::lock_guard<std::mutex> lock(dbMutex);
    db.set(key, value);
}

            sendResponse(clientSocket, "OK\n");
        }
        else if (command == "GET")
        {
            std::string key;
            ss >> key;

            std::string value;

{
    std::lock_guard<std::mutex> lock(dbMutex);
    value = db.get(key);
}
            value += "\n";

            sendResponse(clientSocket, value);
        }
        else if (command == "DEL")
        {
            std::string key;
            ss >> key;

            bool deleted;

{
    std::lock_guard<std::mutex> lock(dbMutex);
    deleted = db.del(key);
}

            std::string response = deleted ? "OK\n" : "NULL\n";

            sendResponse(clientSocket, response);
        }
        else if (command == "EXISTS")
        {
            std::string key;
            ss >> key;

            bool found = db.exists(key);

            std::string response = found ? "TRUE\n" : "FALSE\n";

            sendResponse(clientSocket, response);
        }
        else if (command == "SIZE")
        {
            std::string response =
                std::to_string(db.size()) + "\n";

            sendResponse(clientSocket, response);
        }
        else if (command == "CLEAR")
        {
            {
    std::lock_guard<std::mutex> lock(dbMutex);
    db.clear();
}

            

            sendResponse(clientSocket, "OK\n");
        }
        else
        {
           

            sendResponse(clientSocket, "ERROR: Unknown Command\n");
        }
    }

    close(clientSocket);
}

void Server::start()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1)
    {
        std::cout << "Failed to create socket!" << std::endl;
        return;
    }

    sockaddr_in serverAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);
if (bind(serverSocket,
         (struct sockaddr *)&serverAddress,
         sizeof(serverAddress)) < 0)
{
    perror("Bind failed");
    close(serverSocket);
    return;
}
if (listen(serverSocket, 5) < 0)
{
    std::cout << "Listen failed!" << std::endl;
    close(serverSocket);
    return;
}

std::cout << "MemDB Server is listening on port 8080..." << std::endl;


    while (true)
{
    sockaddr_in clientAddress;
    socklen_t clientSize = sizeof(clientAddress);

    int clientSocket = accept(
        serverSocket,
        (struct sockaddr *)&clientAddress,
        &clientSize);

    if (clientSocket < 0)
    {
        std::cout << "Failed to accept client!" << std::endl;
        continue;
    }
    std::thread clientThread(
    &Server::handleClient,
    this,
    clientSocket);

clientThread.detach();

}
}