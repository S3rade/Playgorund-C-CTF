// src/server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <sys/stat.h>

#define PORT 8888
#define BUFFER_SIZE 1024

// Function to load a file from disk
char* load_file(const char *filename, const char *mode, long *out_size) {
    FILE *file;
    char *buffer;
    long file_size;

    file = fopen(filename, mode);
    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    if (out_size) {
        *out_size = file_size;
    }

    return buffer;
}

// Function to determine if the path refers to a static file (CSS, JS, etc.)
int is_static_file_request(const char *path) {
    return strncmp(path, "../static/", 8) == 0;
}
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
        memset(buffer, 0, BUFFER_SIZE);
        recv(client_socket, buffer, BUFFER_SIZE, 0);

        char method[8], path[1024];
        sscanf(buffer, "%s %s", method, path);

        char *response = NULL;
        long response_size = 0;

        // Check if the request is for a static file
        if (is_static_file_request(path)) {
            char filepath[1024];
            snprintf(filepath, sizeof(filepath), ".%s", path);  // Prepend '.' to the path to serve from local dir
            response = load_file(filepath, "rb", &response_size);  // Load static file

            // Check if the file was found
            if (response != NULL) {
                // Send appropriate headers for CSS file
                const char *headers =
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/css\r\n"
                    "Connection: close\r\n"
                    "\r\n";
                send(client_socket, headers, strlen(headers), 0);
                send(client_socket, response, response_size, 0);
                free(response);
            } else {
                // File not found (404)
                const char *error_response =
                    "HTTP/1.1 404 Not Found\r\n"
                    "Content-Type: text/html\r\n"
                    "Connection: close\r\n"
                    "\r\n"
                    "<html><body><h1>404 File Not Found</h1></body></html>";
                send(client_socket, error_response, strlen(error_response), 0);
            }
        } else {
            // Create response headers for HTML pages
            const char *headers =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Connection: close\r\n"
                "\r\n";

            if (strcmp(path, "/") == 0) {
                response = load_file("../templates/index.html", "rb", &response_size);
            } else if (strcmp(path, "/login") == 0) {
                response = load_file("../templates/login.html", "rb", &response_size);
            } else if (strcmp(path, "/register") == 0) {
                response = load_file("../templates/register.html", "rb", &response_size);
            } else {
                // Handle 404
                response = load_file("templates/404.html", "rb", &response_size);
                if (response == NULL) {
                    response = strdup("<html><body><h1>404 Page Not Found</h1></body></html>");
                    response_size = strlen(response);
                }
            }

            if (response != NULL) {
                send(client_socket, headers, strlen(headers), 0);
                send(client_socket, response, response_size, 0);
                free(response);
            }
        }

        closesocket(client_socket);
    }

    // Cleanup
    closesocket(server_socket);
    WSACleanup();
}
