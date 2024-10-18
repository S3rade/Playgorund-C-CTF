#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <winsock2.h>  // For Windows networking
#pragma comment(lib, "Ws2_32.lib")  // Link winsock library

#define BUFFER_SIZE 4096

// Function prototypes
void handle_client(SOCKET client_socket);
void create_table_if_not_exists(sqlite3 *db);
int register_user(sqlite3 *db, const char *username, const char *password);
int login_user(sqlite3 *db, const char *username, const char *password);

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int c;

    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Could not create socket: %d\n", WSAGetLastError());
        return 1;
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    // Bind
    bind(server_socket, (struct sockaddr *)&server, sizeof(server));

    // Listen for incoming connections
    listen(server_socket, 3);

    printf("Server listening on port 8080\n");

    // Initialize SQLite
    sqlite3 *db;
    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Ensure the users table is created
    create_table_if_not_exists(db);

    // Accept and handle clients
    c = sizeof(struct sockaddr_in);
    while ((client_socket = accept(server_socket, (struct sockaddr *)&client, &c)) != INVALID_SOCKET) {
        printf("Client connected\n");
        handle_client(client_socket);
        closesocket(client_socket);
    }

    sqlite3_close(db);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}

// Function to handle a client request
void handle_client(SOCKET client_socket) {
    char buffer[BUFFER_SIZE];
    recv(client_socket, buffer, BUFFER_SIZE, 0);

    // Basic HTTP handling
    if (strstr(buffer, "GET /login")) {
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                               "<html><body><h1>Login</h1>"
                               "<form action='/login' method='POST'>"
                               "Username: <input type='text' name='username'><br>"
                               "Password: <input type='password' name='password'><br>"
                               "<input type='submit' value='Login'></form></body></html>";
        send(client_socket, response, strlen(response), 0);
    } else if (strstr(buffer, "GET /register")) {
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                               "<html><body><h1>Register</h1>"
                               "<form action='/register' method='POST'>"
                               "Username: <input type='text' name='username'><br>"
                               "Password: <input type='password' name='password'><br>"
                               "<input type='submit' value='Register'></form></body></html>";
        send(client_socket, response, strlen(response), 0);
    } else if (strstr(buffer, "POST /register")) {
        // Handle registration form submission
        // Parse buffer to extract form data (username and password)
        // Call register_user(db, username, password)
    } else if (strstr(buffer, "POST /login")) {
        // Handle login form submission
        // Parse buffer to extract form data (username and password)
        // Call login_user(db, username, password)
    } else {
        const char *response = "HTTP/1.1 404 Not Found\r\n\r\n";
        send(client_socket, response, strlen(response), 0);
    }
}

// Function to create the users table if it doesn't exist
void create_table_if_not_exists(sqlite3 *db) {
    char *err_msg = 0;
    const char *sql = "CREATE TABLE IF NOT EXISTS users ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "username TEXT NOT NULL UNIQUE, "
                      "password TEXT NOT NULL);";

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Table created successfully\n");
    }
}

// Function to register a user
int register_user(sqlite3 *db, const char *username, const char *password) {
    char *err_msg = 0;
    char sql[256];

    sprintf(sql, "INSERT INTO users(username, password) VALUES('%s', '%s');", username, password);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 0;
    } else {
        printf("User registered successfully\n");
        return 1;
    }
}

// Function to log in a user
int login_user(sqlite3 *db, const char *username, const char *password) {
    char *err_msg = 0;
    sqlite3_stmt *res;
    char sql[256];

    sprintf(sql, "SELECT * FROM users WHERE username='%s' AND password='%s';", username, password);

    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    rc = sqlite3_step(res);
    if (rc == SQLITE_ROW) {
        printf("User logged in successfully\n");
        sqlite3_finalize(res);
        return 1;
    } else {
        printf("Invalid username or password\n");
        sqlite3_finalize(res);
        return 0;
    }
}
