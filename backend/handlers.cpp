#include "handlers.h"

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
