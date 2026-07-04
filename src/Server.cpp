#include "../include/Server.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <cerrno>
Server::Server(Database &database) : db(database)
{
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
std::cout << "Bytes received = " << bytesReceived << std::endl;
    if (bytesReceived <= 0)
    {
        break;
    }

    std::cout << "Received: " << buffer << std::endl;
std::string message(buffer, bytesReceived);

    std::stringstream ss(message);

    std::string command;
    ss >> command;

    if (command == "PING")
    {
        const char *response = "PONG\n";

        send(clientSocket,
             response,
             strlen(response),
             0);
    }
    else if (command == "SET")
    {
        std::string key, value;

        ss >> key >> value;

        db.set(key, value);

        const char *response = "OK\n";

        send(clientSocket,
             response,
             strlen(response),
             0);
    }
    else if (command == "GET")
    {
        std::string key;

        ss >> key;

        std::string value = db.get(key);

        value += "\n";

        send(clientSocket,
             value.c_str(),
             value.length(),
             0);
    }
    else if (command == "DEL")
{
    std::string key;
    ss >> key;

    bool deleted = db.del(key);

    std::string response;

    if (deleted)
        response = "OK\n";
    else
        response = "NULL\n";

    send(clientSocket,
         response.c_str(),
         response.length(),
         0);
}
else if (command == "EXISTS")
{
    std::string key;
    ss >> key;

    bool found = db.exists(key);

    std::string response;

    if (found)
        response = "TRUE\n";
    else
        response = "FALSE\n";

    send(clientSocket,
         response.c_str(),
         response.length(),
         0);
}
else if (command == "SIZE")
{
    size_t count = db.size();

    std::string response = std::to_string(count) + "\n";

    send(clientSocket,
         response.c_str(),
         response.length(),
         0);
}
else if (command == "CLEAR")
{
    db.clear();

    const char *response = "OK\n";

    send(clientSocket,
         response,
         strlen(response),
         0);
}
}

close(clientSocket);
}
}