// src/server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 8888
#define BUFFER_SIZE 1024

void start_server() {
    WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_size = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    // Set up the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Listen for connections
    listen(server_socket, 1);

    // Accept connections
    while ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size))) {
        // Read request
        recv(client_socket, buffer, BUFFER_SIZE, 0);

        // Simple HTTP response
        const char *response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<html><body><h1>Quiz Game Running!</h1></body></html>";

        send(client_socket, response, strlen(response), 0);
        closesocket(client_socket);
    }

    // Cleanup
    closesocket(server_socket);
    WSACleanup();
}
