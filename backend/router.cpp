#include "router.h"

//   router for HTTP requests to appropriate handlers
string routeRequest(DataStore& store, HttpRequest req) {
    //   CORS preflight handler
    if (req.method == "OPTIONS") {
        return buildHttpResponse(200, "OK", "");
    }
    
    //   login endpoint
    if (req.method == "POST" && req.path == "/api/login") {
        return handleLogin(store, req.body);
    }
    
    //   getter for all courses endpoint
    if (req.method == "GET" && req.path == "/api/courses") {
        return handleGetCourses(store);
    }
    
    //   getter for all students endpoint (for teacher)
    if (req.method == "GET" && req.path == "/api/students") {
        return handleGetStudents(store);
    }
    
    //   getter for student's enrolled courses endpoint
    if (req.method == "GET" && req.path.find("/api/students/") == 0 && req.path.find("/courses") != string::npos) {
        size_t start = 14; // length of "/api/students/"
        size_t end = req.path.find("/courses");
        string studentId = req.path.substr(start, end - start);
        return handleGetStudentCourses(store, studentId);
    }
    
    //   getter for enrolled students for a course endpoint
    if (req.method == "GET" && req.path.find("/api/courses/") == 0 && req.path.find("/students") != string::npos) {
        size_t start = 13; // length of "/api/courses/"
        size_t end = req.path.find("/students");
        string courseId = req.path.substr(start, end - start);
        return handleGetCourseStudents(store, courseId);
    }
    
    //   getter for student grades endpoint
    if (req.method == "GET" && req.path.find("/api/grades/") == 0) {
        string studentId = req.path.substr(12); // Extract student ID
        return handleGetStudentGrades(store, studentId);
    }
    
    //   getter for teacher's grades endpoint
    if (req.method == "GET" && req.path.find("/api/teacher/") == 0 && req.path.find("/grades") != string::npos) {
        size_t start = 13; // length of "/api/teacher/"
        size_t end = req.path.find("/grades");
        string teacherId = req.path.substr(start, end - start);
        return handleGetTeacherGrades(store, teacherId);
    }
    
    //   enroll in course endpoint
    if (req.method == "POST" && req.path == "/api/enroll") {
        return handleEnrollCourse(store, req.body);
    }
    
    //   unenroll from course endpoint
    if (req.method == "POST" && req.path == "/api/unenroll") {
        return handleUnenrollCourse(store, req.body);
    }
    
    //   add/update grade endpoint
    if (req.method == "POST" && req.path == "/api/grades") {
        return handleAddGrade(store, req.body);
    }
    
    //   delete grade endpoint
    if (req.method == "DELETE" && req.path == "/api/grades") {
        return handleDeleteGrade(store, req.body);
    }
    
    //   404 Not Found
    json response;
    response["error"] = "Endpoint not found";
    return buildHttpResponse(404, "Not Found", response.dump());
}
