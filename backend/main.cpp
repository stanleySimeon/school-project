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
        
        //   reader for incoming request data
        char buffer[4096] = {0};
        read(clientSocket, buffer, 4096);
        string requestStr(buffer);
        
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
