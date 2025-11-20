#include "handlers.h"
#include <sstream>
#include <iomanip>
#include <ctime>

// handler for user login authentication
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

// handler for user signup
string handleSignup(DataStore& store, string body) {
    // Validate body is not empty
    if (body.empty()) {
        json errorResponse;
        errorResponse["success"] = false;
        errorResponse["message"] = "Request body is empty";
        return buildHttpResponse(400, "Bad Request", errorResponse.dump());
    }
    
    json requestData;
    try {
        requestData = json::parse(body);
    } catch (const json::parse_error& e) {
        json errorResponse;
        errorResponse["success"] = false;
        errorResponse["message"] = "Invalid JSON format";
        return buildHttpResponse(400, "Bad Request", errorResponse.dump());
    }
    
    // Validate required fields
    if (!requestData.contains("username") || !requestData.contains("password") || 
        !requestData.contains("firstName") || !requestData.contains("lastName") ||
        !requestData.contains("dateOfBirth") || !requestData.contains("email") ||
        !requestData.contains("role")) {
        json errorResponse;
        errorResponse["success"] = false;
        errorResponse["message"] = "Missing required fields";
        return buildHttpResponse(400, "Bad Request", errorResponse.dump());
    }
    
    string username = requestData["username"];
    string password = requestData["password"];
    string firstName = requestData["firstName"];
    string lastName = requestData["lastName"];
    string dateOfBirth = requestData["dateOfBirth"];
    string email = requestData["email"];
    string role = requestData["role"];
    
    // generator for unique user ID based on role and timestamp
    time_t now = time(0);
    stringstream ss;
    
    if (role == "teacher") {
        // teacher ID format: T### (auto-incremented)
        int teacherCount = store.getTeacherCount();
        ss << "T" << setfill('0') << setw(3) << (teacherCount + 1);
    } else {
        // student ID format: FLNNN (First+Last+Number)
        int studentCount = store.getStudentCount();
        char firstInitial = toupper(firstName[0]);
        char lastInitial = toupper(lastName[0]);
        ss << firstInitial << lastInitial << setfill('0') << setw(3) << (studentCount + 1);
    }
    
    string userId = ss.str();
    
    // creator for new user
    User newUser;
    newUser.id = userId;
    newUser.username = username;
    newUser.password = password;
    newUser.role = role;
    newUser.name = firstName + " " + lastName;
    newUser.firstName = firstName;
    newUser.lastName = lastName;
    newUser.dateOfBirth = dateOfBirth;
    newUser.email = email;
    
    // adder for user to datastore
    store.addUser(newUser);
    
    // handler for course assignment/enrollment
    if (requestData.contains("courseId") && !requestData["courseId"].is_null()) {
        try {
            string courseId = requestData["courseId"];
            if (!courseId.empty()) {
                if (role == "teacher") {
                    // assign teacher to course
                    store.assignTeacherToCourse(userId, courseId);
                } else if (role == "student") {
                    // enroll student in course
                    store.enrollStudent(userId, courseId);
                }
            }
        } catch (...) {
            // ignore course assignment/enrollment errors for now
        }
    }
    
    json response;
    response["success"] = true;
    response["user"] = {
        {"id", newUser.id},
        {"username", newUser.username},
        {"role", newUser.role}
    };
    
    return buildHttpResponse(201, "Created", response.dump());
}

// getter for list of all students
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

// getter for all courses
string handleGetCourses(DataStore& store) {
    vector<Course> courses = store.getAllCourses();
    json response = json::array();
    
    for (auto& course : courses) {
        User* teacher = store.getUserById(course.teacherId);
        json courseObj;
        courseObj["id"] = course.id;
        courseObj["name"] = course.name;
        courseObj["teacherId"] = course.teacherId;
        courseObj["teacherName"] = teacher ? teacher->username : "Unknown";
        courseObj["description"] = course.description;
        response.push_back(courseObj);
    }
    
    return buildHttpResponse(200, "OK", response.dump());
}

//   getter for enrolled courses for a student
string handleGetStudentCourses(DataStore& store, string studentId) {
    vector<Course> courses = store.getEnrolledCourses(studentId);
    json response = json::array();
    
    for (auto& course : courses) {
        User* teacher = store.getUserById(course.teacherId);
        json courseObj;
        courseObj["id"] = course.id;
        courseObj["name"] = course.name;
        courseObj["teacherId"] = course.teacherId;
        courseObj["teacherName"] = teacher ? teacher->username : "Unknown";
        courseObj["description"] = course.description;
        response.push_back(courseObj);
    }
    
    return buildHttpResponse(200, "OK", response.dump());
}

//   enroller for student in a course
string handleEnrollCourse(DataStore& store, string body) {
    json requestData = json::parse(body);
    string studentId = requestData["studentId"];
    string courseId = requestData["courseId"];
    
    store.enrollStudent(studentId, courseId);
    
    json response;
    response["success"] = true;
    response["message"] = "Enrolled successfully";
    return buildHttpResponse(200, "OK", response.dump());
}

//   unenroller for student from a course
string handleUnenrollCourse(DataStore& store, string body) {
    json requestData = json::parse(body);
    string studentId = requestData["studentId"];
    string courseId = requestData["courseId"];
    
    store.unenrollStudent(studentId, courseId);
    
    json response;
    response["success"] = true;
    response["message"] = "Unenrolled successfully";
    return buildHttpResponse(200, "OK", response.dump());
}

// getter for all grades for teacher view (for their courses)
string handleGetTeacherGrades(DataStore& store, string teacherId) {
    vector<Grade> grades = store.getGradesByTeacher(teacherId);
    json response = json::array();
    
    for (auto& grade : grades) {
        User* student = store.getUserById(grade.studentId);
        Course* course = store.getCourseById(grade.courseId);
        json gradeObj;
        gradeObj["studentId"] = grade.studentId;
        gradeObj["studentName"] = student ? student->name : "Unknown";
        gradeObj["courseId"] = grade.courseId;
        gradeObj["courseName"] = course ? course->name : "Unknown";
        gradeObj["score"] = grade.score;
        gradeObj["note"] = grade.note;
        gradeObj["teacherId"] = grade.teacherId;
        response.push_back(gradeObj);
    }
    
    return buildHttpResponse(200, "OK", response.dump());
}

//   getter for grades for a specific student with course info
string handleGetStudentGrades(DataStore& store, string studentId) {
    vector<Grade> grades = store.getGradesByStudent(studentId);
    json response = json::array();
    
    for (auto& grade : grades) {
        Course* course = store.getCourseById(grade.courseId);
        json gradeObj;
        gradeObj["courseId"] = grade.courseId;
        gradeObj["courseName"] = course ? course->name : "Unknown";
        gradeObj["score"] = grade.score;
        gradeObj["note"] = grade.note;
        gradeObj["teacherId"] = grade.teacherId;
        response.push_back(gradeObj);
    }
    
    return buildHttpResponse(200, "OK", response.dump());
}

//   getter for enrolled students for a specific course
string handleGetCourseStudents(DataStore& store, string courseId) {
    vector<User> students = store.getStudentsByCourse(courseId);
    json response = json::array();
    
    for (auto& student : students) {
        json studentObj;
        studentObj["id"] = student.id;
        studentObj["username"] = student.username;
        studentObj["name"] = student.name;
        studentObj["role"] = student.role;
        response.push_back(studentObj);
    }
    
    return buildHttpResponse(200, "OK", response.dump());
}

//   adder or updater for a grade
string handleAddGrade(DataStore& store, string body) {
    json requestData = json::parse(body);
    string studentId = requestData["studentId"];
    string courseId = requestData["courseId"];
    int score = requestData["score"];
    string note = requestData["note"];
    string teacherId = requestData["teacherId"];
    
    // validator that student exists and is enrolled in the course
    if (!store.isEnrolled(studentId, courseId)) {
        json response;
        response["success"] = false;
        response["message"] = "Student is not enrolled in this course";
        return buildHttpResponse(400, "Bad Request", response.dump());
    }
    
    store.addOrUpdateGrade(studentId, courseId, score, note, teacherId);
    
    json response;
    response["success"] = true;
    response["message"] = "Grade added/updated successfully";
    return buildHttpResponse(200, "OK", response.dump());
}

// to be able to delete a grade
string handleDeleteGrade(DataStore& store, string body) {
    json requestData = json::parse(body);
    string studentId = requestData["studentId"];
    string courseId = requestData["courseId"];
    
    store.deleteGrade(studentId, courseId);
    
    json response;
    response["success"] = true;
    response["message"] = "Grade deleted successfully";
    return buildHttpResponse(200, "OK", response.dump());
}
