#include "tcpservice.h"

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

void TCPService::run()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    while (true) // Sending buffer with mutex protection
    {
        std::lock_guard<std::mutex> lock(buffer_mutex);
        /* std::cout << "Sending data: ";
        for (size_t i = 0; i < sizeof(buffer); i++)
        {
            std::cout << static_cast<int>(buffer[i]) << " ";
        }
        std::cout << std::endl; */

        // Sending buffer to client
        /* if (write(new_socket, buffer, sizeof(buffer)) < 0)
        {
            perror("write failed");
        } */

        if (send(new_socket, buffer, sizeof(buffer), 0) < 0)
        {
            std::cerr << "Send failed!" << std::endl;
        }

        /* std::cout << "Buffer contents (binary): ";
        for (size_t i = 0; i < 4; ++i)
        {
            for (int j = 7; j >= 0; --j)
            {
                std::cout << ((buffer[i] >> j) & 1);
            }
            std::cout << " ";
        }
        std::cout << std::endl; */
    }

    close(new_socket);
    close(server_fd);
}