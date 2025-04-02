#include <connectionhandler.h>
#include "sqlitedriver.h"
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <datarequest.h>
#include <sys/socket.h>
#include <unistd.h>
#include <functional>
#include <iostream>


void ConnectionHandler::operator()()
{
    int sockfd;
    struct sockaddr_in servaddr, cli;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket creation failed");
        return;
    }

    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY; // Any address
    servaddr.sin_port = htons(1666); // Port

    // Bind the socket to the address and port
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        close(sockfd);
        return;
    }

    // Start listening for incoming connections
    if (listen(sockfd, 5) < 0) {
        perror("listen failed");
        close(sockfd);
        return;
    }

    while (true ==  ok_to_handle_reads.load())
    {
        // Accept a new connection
        std::cout << "Waiting for a connection..." << std::endl;
        socklen_t len = sizeof(cli);
        int connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
        if (connfd < 0) {
            perror("accept failed");
            continue;
        }

        // Handle the connection
        // we should handle a way to read more then 1024 bytes at a time
        char buffer[1024] = {0};
        size_t bytes_read = read(connfd, buffer, sizeof(buffer));
        //std::ostringstream command;
        //command << std::string(buffer, bytes_read);
        if (buffer[bytes_read - 1] == '\n') {
            // we received a complete command now handled it
        }   
       
        std::function<void(std::string)> callback =
            [connfd](std::string response) 
        {
            write(connfd, response.c_str(), response.size());
            close(connfd);
        };

        DataRequest request(
            std::string(buffer, bytes_read), 
            "AAA111", callback);

        //d_reader.enqueueRequest(request);
    };
    

    close(sockfd);
};