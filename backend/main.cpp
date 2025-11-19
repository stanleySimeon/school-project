/*
 * School Management System - Backend Server
 * A simple REST API server for managing teachers, students, notes, and grades
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// DATA MODELS - Define user and grade structures

struct User {
    string id;
    string username;
    string password;
    string role; // "teacher" or "student"
};

struct Grade {
    string studentId;
    string subject;
    int score;
    string note;
    string updatedBy; // teacher id
};

// DATA STORAGE - Manages users and grades with JSON persistence

class DataStore {
private:
    vector<User> users;
    vector<Grade> grades;
    string dataFile = "data.json";

public:
    DataStore() {
        loadData();
    }

    // Load data from JSON file
    void loadData() {
        ifstream file(dataFile);
        if (file.is_open()) {
            json data;
            file >> data;
            
            // Load users
            if (data.contains("users")) {
                for (auto& u : data["users"]) {
                    User user;
                    user.id = u["id"];
                    user.username = u["username"];
                    user.password = u["password"];
                    user.role = u["role"];
                    users.push_back(user);
                }
            }
            
            // Load grades
            if (data.contains("grades")) {
                for (auto& g : data["grades"]) {
                    Grade grade;
                    grade.studentId = g["studentId"];
                    grade.subject = g["subject"];
                    grade.score = g["score"];
                    grade.note = g["note"];
                    grade.updatedBy = g["updatedBy"];
                    grades.push_back(grade);
                }
            }
            
            file.close();
        } else {
            // Initialize with default data
            initializeDefaultData();
        }
    }

    // Save data to JSON file
    void saveData() {
        json data;
        
        // Save users
        data["users"] = json::array();
        for (auto& u : users) {
            json user;
            user["id"] = u.id;
            user["username"] = u.username;
            user["password"] = u.password;
            user["role"] = u.role;
            data["users"].push_back(user);
        }
        
        // Save grades
        data["grades"] = json::array();
        for (auto& g : grades) {
            json grade;
            grade["studentId"] = g.studentId;
            grade["subject"] = g.subject;
            grade["score"] = g.score;
            grade["note"] = g.note;
            grade["updatedBy"] = g.updatedBy;
            data["grades"].push_back(grade);
        }
        
        ofstream file(dataFile);
        file << data.dump(4);
        file.close();
    }

    // Initialize with sample data
    void initializeDefaultData() {
        // Add a teacher
        users.push_back({"T001", "teacher", "teacher123", "teacher"});
        
        // Add students
        users.push_back({"S001", "john", "john123", "student"});
        users.push_back({"S002", "jane", "jane123", "student"});
        users.push_back({"S003", "bob", "bob123", "student"});
        
        // Add sample grades
        grades.push_back({"S001", "Mathematics", 85, "Good progress", "T001"});
        grades.push_back({"S001", "English", 90, "Excellent work", "T001"});
        grades.push_back({"S002", "Mathematics", 78, "Needs improvement", "T001"});
        grades.push_back({"S002", "English", 88, "Very good", "T001"});
        grades.push_back({"S003", "Mathematics", 92, "Outstanding", "T001"});
        
        saveData();
    }

    // Authenticate user
    User* authenticateUser(string username, string password) {
        for (auto& user : users) {
            if (user.username == username && user.password == password) {
                return &user;
            }
        }
        return nullptr;
    }

    // Get all students
    vector<User> getAllStudents() {
        vector<User> students;
        for (auto& user : users) {
            if (user.role == "student") {
                students.push_back(user);
            }
        }
        return students;
    }

    // Get grades for a student
    vector<Grade> getGradesByStudent(string studentId) {
        vector<Grade> studentGrades;
        for (auto& grade : grades) {
            if (grade.studentId == studentId) {
                studentGrades.push_back(grade);
            }
        }
        return studentGrades;
    }

    // Get all grades (for teacher)
    vector<Grade> getAllGrades() {
        return grades;
    }

    // Add or update grade
    void addOrUpdateGrade(string studentId, string subject, int score, string note, string teacherId) {
        // Check if grade exists
        for (auto& grade : grades) {
            if (grade.studentId == studentId && grade.subject == subject) {
                grade.score = score;
                grade.note = note;
                grade.updatedBy = teacherId;
                saveData();
                return;
            }
        }
        
        // Add new grade
        grades.push_back({studentId, subject, score, note, teacherId});
        saveData();
    }

    // Delete grade
    void deleteGrade(string studentId, string subject) {
        for (auto it = grades.begin(); it != grades.end(); ++it) {
            if (it->studentId == studentId && it->subject == subject) {
                grades.erase(it);
                saveData();
                return;
            }
        }
    }
};

// HTTP REQUEST PARSER - Parse incoming HTTP requests

struct HttpRequest {
    string method;
    string path;
    map<string, string> headers;
    string body;
};

// Parse HTTP request string into structured data
HttpRequest parseHttpRequest(string requestStr) {
    HttpRequest req;
    istringstream stream(requestStr);
    string line;
    
    // Parse request line
    getline(stream, line);
    istringstream requestLine(line);
    requestLine >> req.method >> req.path;
    
    // Parse headers
    while (getline(stream, line) && line != "\r" && !line.empty()) {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos) {
            string key = line.substr(0, colonPos);
            string value = line.substr(colonPos + 2);
            if (value.back() == '\r') value.pop_back();
            req.headers[key] = value;
        }
    }
    
    // Parse body
    string bodyContent;
    while (getline(stream, line)) {
        bodyContent += line;
    }
    req.body = bodyContent;
    
    return req;
}

// HTTP RESPONSE BUILDER - Build HTTP response with headers

// Build formatted HTTP response
string buildHttpResponse(int statusCode, string statusText, string body, string contentType = "application/json") {
    ostringstream response;
    response << "HTTP/1.1 " << statusCode << " " << statusText << "\r\n";
    response << "Content-Type: " << contentType << "\r\n";
    response << "Content-Length: " << body.length() << "\r\n";
    response << "Access-Control-Allow-Origin: *\r\n";
    response << "Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS\r\n";
    response << "Access-Control-Allow-Headers: Content-Type, Authorization\r\n";
    response << "Connection: close\r\n";
    response << "\r\n";
    response << body;
    return response.str();
}

// API HANDLERS - Handle specific API endpoints

// Handle user login authentication
string handleLogin(DataStore& store, string body) {
    json requestData = json::parse(body);
    string username = requestData["username"];
    string password = requestData["password"];
    
    User* user = store.authenticateUser(username, password);
    
    if (user != nullptr) {
        json response;
        response["success"] = true;
        response["user"] = {
            {"id", user->id},
            {"username", user->username},
            {"role", user->role}
        };
        return buildHttpResponse(200, "OK", response.dump());
    } else {
        json response;
        response["success"] = false;
        response["message"] = "Invalid credentials";
        return buildHttpResponse(401, "Unauthorized", response.dump());
    }
}

// Get list of all students
string handleGetStudents(DataStore& store) {
    vector<User> students = store.getAllStudents();
    json response = json::array();
    
    for (auto& student : students) {
        json studentObj;
        studentObj["id"] = student.id;
        studentObj["username"] = student.username;
        response.push_back(studentObj);
    }
    
    return buildHttpResponse(200, "OK", response.dump());
}

// Get all grades for teacher view
string handleGetAllGrades(DataStore& store) {
    vector<Grade> grades = store.getAllGrades();
    json response = json::array();
    
    for (auto& grade : grades) {
        json gradeObj;
        gradeObj["studentId"] = grade.studentId;
        gradeObj["subject"] = grade.subject;
        gradeObj["score"] = grade.score;
        gradeObj["note"] = grade.note;
        gradeObj["updatedBy"] = grade.updatedBy;
        response.push_back(gradeObj);
    }
    
    return buildHttpResponse(200, "OK", response.dump());
}

// Get grades for a specific student
string handleGetStudentGrades(DataStore& store, string studentId) {
    vector<Grade> grades = store.getGradesByStudent(studentId);
    json response = json::array();
    
    for (auto& grade : grades) {
        json gradeObj;
        gradeObj["subject"] = grade.subject;
        gradeObj["score"] = grade.score;
        gradeObj["note"] = grade.note;
        response.push_back(gradeObj);
    }
    
    return buildHttpResponse(200, "OK", response.dump());
}

// Add or update a grade
string handleAddGrade(DataStore& store, string body) {
    json requestData = json::parse(body);
    string studentId = requestData["studentId"];
    string subject = requestData["subject"];
    int score = requestData["score"];
    string note = requestData["note"];
    string teacherId = requestData["teacherId"];
    
    store.addOrUpdateGrade(studentId, subject, score, note, teacherId);
    
    json response;
    response["success"] = true;
    response["message"] = "Grade added/updated successfully";
    return buildHttpResponse(200, "OK", response.dump());
}

// Delete a grade
string handleDeleteGrade(DataStore& store, string body) {
    json requestData = json::parse(body);
    string studentId = requestData["studentId"];
    string subject = requestData["subject"];
    
    store.deleteGrade(studentId, subject);
    
    json response;
    response["success"] = true;
    response["message"] = "Grade deleted successfully";
    return buildHttpResponse(200, "OK", response.dump());
}

// REQUEST ROUTER - Route requests to appropriate handlers

// Route incoming requests to correct handler
string routeRequest(DataStore& store, HttpRequest& req) {
    // Handle CORS preflight
    if (req.method == "OPTIONS") {
        return buildHttpResponse(200, "OK", "");
    }
    
    // Login endpoint
    if (req.method == "POST" && req.path == "/api/login") {
        return handleLogin(store, req.body);
    }
    
    // Get all students (for teacher)
    if (req.method == "GET" && req.path == "/api/students") {
        return handleGetStudents(store);
    }
    
    // Get all grades (for teacher)
    if (req.method == "GET" && req.path == "/api/grades") {
        return handleGetAllGrades(store);
    }
    
    // Get student grades
    if (req.method == "GET" && req.path.find("/api/grades/") == 0) {
        string studentId = req.path.substr(12); // Extract student ID
        return handleGetStudentGrades(store, studentId);
    }
    
    // Add/Update grade
    if (req.method == "POST" && req.path == "/api/grades") {
        return handleAddGrade(store, req.body);
    }
    
    // Delete grade
    if (req.method == "DELETE" && req.path == "/api/grades") {
        return handleDeleteGrade(store, req.body);
    }
    
    // 404 Not Found
    json response;
    response["error"] = "Endpoint not found";
    return buildHttpResponse(404, "Not Found", response.dump());
}

// SERVER MAIN - Initialize and run the HTTP server

// Main server loop
int main() {
    DataStore store;
    
    // Create TCP socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        cerr << "Error creating socket" << endl;
        return 1;
    }
    
    // Allow socket reuse to avoid "address already in use" errors
    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // Configure server address and port
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);
    
    // Bind socket to port 8080
    if (::bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Error binding socket" << endl;
        return 1;
    }
    
    // Listen for incoming connections
    if (listen(serverSocket, 10) < 0) {
        cerr << "Error listening on socket" << endl;
        return 1;
    }
    
    cout << "========================================" << endl;
    cout << "School Management System Backend" << endl;
    cout << "Server running on http://localhost:8080" << endl;
    cout << "========================================" << endl;
    cout << "\nDefault Credentials:" << endl;
    cout << "Teacher - Username: teacher, Password: teacher123" << endl;
    cout << "Student - Username: john, Password: john123" << endl;
    cout << "========================================\n" << endl;
    
    // Main server loop - accept and handle connections
    while (true) {
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        
        // Accept incoming connection
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        
        if (clientSocket < 0) {
            cerr << "Error accepting connection" << endl;
            continue;
        }
        
        // Read incoming request data
        char buffer[4096] = {0};
        read(clientSocket, buffer, 4096);
        string requestStr(buffer);
        
        // Parse HTTP request and route to handler
        HttpRequest req = parseHttpRequest(requestStr);
        cout << "Request: " << req.method << " " << req.path << endl;
        
        // Get response from appropriate handler
        string response = routeRequest(store, req);
        
        // Send response and close connection
        write(clientSocket, response.c_str(), response.length());
        close(clientSocket);
    }
    
    close(serverSocket);
    return 0;
}
