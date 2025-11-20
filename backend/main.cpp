//   School Management System - Backend Server main entry point
//   simple REST API server for managing teachers, students, courses, enrollments, and grades

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include "models.h"
#include "datastore.h"
#include "http.h"
#include "router.h"

using namespace std;

//   main server loop
int main() {
    DataStore store;
    
    //   getter for port from environment or default to 8080
    const char* portEnv = getenv("PORT");
    int port = portEnv ? atoi(portEnv) : 8080;
    
    //   creator for TCP socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        cerr << "Error creating socket" << endl;
        return 1;
    }
    
    //   socket reuse enabler to avoid "address already in use" errors
    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    //   configurator for server address and port
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
    
    //   binder for socket to port 8080
    if (::bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Error binding socket" << endl;
        return 1;
    }
    
    //   listener for incoming connections
    if (listen(serverSocket, 10) < 0) {
        cerr << "Error listening on socket" << endl;
        return 1;
    }
    
    cout << "========================================" << endl;
    cout << "School Management System Backend" << endl;
    cout << "Server running on http://0.0.0.0:" << port << endl;
    cout << "========================================" << endl;
    cout << "\nDefault Credentials:" << endl;
    cout << "Teachers:" << endl;
    cout << "  - mrsmith (Math & CS), msjones (English)" << endl;
    cout << "  - mrwilson (Science), msdavis (History)" << endl;
    cout << "  - Password: teacher123" << endl;
    cout << "Students:" << endl;
    cout << "  - john, jane, bob" << endl;
    cout << "  - Password: john123, jane123, bob123" << endl;
    cout << "========================================\n" << endl;
    
    //   main server loop - accept and handle connections
    while (true) {
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        
        //   acceptor for incoming connection
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        
        if (clientSocket < 0) {
            cerr << "Error accepting connection" << endl;
            continue;
        }
        
        //   reader for incoming request data (read all available data)
        string requestStr;
        char buffer[4096] = {0};
        ssize_t bytesRead;
        
        // Read first chunk
        bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            requestStr = string(buffer);
            
            // Parse headers to check for Content-Length
            size_t headerEnd = requestStr.find("\r\n\r\n");
            if (headerEnd != string::npos) {
                size_t clPos = requestStr.find("Content-Length:");
                if (clPos != string::npos && clPos < headerEnd) {
                    // Extract Content-Length value
                    size_t clStart = clPos + 15; // Length of "Content-Length:"
                    size_t clEnd = requestStr.find("\r\n", clStart);
                    int contentLength = stoi(requestStr.substr(clStart, clEnd - clStart));
                    
                    // Calculate how much body we've already read
                    int bodyStart = headerEnd + 4;
                    int bodyReceived = bytesRead - bodyStart;
                    
                    // Read remaining body if needed
                    while (bodyReceived < contentLength) {
                        bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);
                        if (bytesRead <= 0) break;
                        buffer[bytesRead] = '\0';
                        requestStr += string(buffer);
                        bodyReceived += bytesRead;
                    }
                }
            }
        }
        
        //   parser for HTTP request and route to handler
        HttpRequest req = parseHttpRequest(requestStr);
        cout << "Request: " << req.method << " " << req.path << endl;
        
        //   getter for response from appropriate handler
        string response = routeRequest(store, req);
        
        //   sender for response and close connection
        write(clientSocket, response.c_str(), response.length());
        close(clientSocket);
    }
    
    close(serverSocket);
    return 0;
}
