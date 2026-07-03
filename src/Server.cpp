#include "../include/Server.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

Server::Server()
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
             (struct sockaddr*)&serverAddress,
             sizeof(serverAddress)) < 0)
    {
        std::cout << "Bind failed!" << std::endl;
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

sockaddr_in clientAddress;
socklen_t clientSize = sizeof(clientAddress);

int clientSocket = accept(
    serverSocket,
    (struct sockaddr *)&clientAddress,
    &clientSize
);

if (clientSocket < 0)
{
    std::cout << "Failed to accept client!" << std::endl;
}
else
{
    std::cout << "Client connected successfully!" << std::endl;
    close(clientSocket);
}

close(serverSocket);
}