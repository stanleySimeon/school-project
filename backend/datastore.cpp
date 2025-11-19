#include "datastore.h"

DataStore::DataStore() {
    loadData();
}

//   loader for data from JSON file
void DataStore::loadData() {
    ifstream file(dataFile);
    if (file.is_open()) {
        json data;
        file >> data;
        
        //   loader for users
        if (data.contains("users")) {
            for (auto& u : data["users"]) {
                User user;
                user.id = u.value("id", "");
                user.username = u.value("username", "");
                user.password = u.value("password", "");
                user.role = u.value("role", "");
                user.name = u.value("name", "");
                user.firstName = u.value("firstName", "");
                user.lastName = u.value("lastName", "");
                user.dateOfBirth = u.value("dateOfBirth", "");
                user.email = u.value("email", "");
                users.push_back(user);
            }
        }
        
        //   loader for courses
        if (data.contains("courses")) {
            for (auto& c : data["courses"]) {
                Course course;
                course.id = c.value("id", "");
                course.name = c.value("name", "");
                course.teacherId = c.value("teacherId", "");
                course.description = c.value("description", "");
                courses.push_back(course);
            }
        }
        
        //   loader for enrollments
        if (data.contains("enrollments")) {
            for (auto& e : data["enrollments"]) {
                Enrollment enrollment;
                enrollment.studentId = e.value("studentId", "");
                enrollment.courseId = e.value("courseId", "");
                enrollments.push_back(enrollment);
            }
        }
        
        //   loader for grades
        if (data.contains("grades")) {
            for (auto& g : data["grades"]) {
                Grade grade;
                grade.studentId = g.value("studentId", "");
                grade.courseId = g.value("courseId", "");
                grade.score = g.value("score", 0);
                grade.note = g.value("note", "");
                grade.teacherId = g.value("teacherId", "");
                grades.push_back(grade);
            }
        }
        
        file.close();
    } else {
        //   initializer with default data
        initializeDefaultData();
    }
}

//   saver for data to JSON file
void DataStore::saveData() {
    json data;
    
    //   saver for users
    data["users"] = json::array();
    for (auto& u : users) {
        json user;
        user["id"] = u.id;
        user["username"] = u.username;
        user["password"] = u.password;
        user["role"] = u.role;
        user["firstName"] = u.firstName;
        user["lastName"] = u.lastName;
        user["dateOfBirth"] = u.dateOfBirth;
        user["email"] = u.email;
        user["name"] = u.name;
        data["users"].push_back(user);
    }
    
    //   saver for courses
    data["courses"] = json::array();
    for (auto& c : courses) {
        json course;
        course["id"] = c.id;
        course["name"] = c.name;
        course["teacherId"] = c.teacherId;
        course["description"] = c.description;
        data["courses"].push_back(course);
    }
    
    //   saver for enrollments
    data["enrollments"] = json::array();
    for (auto& e : enrollments) {
        json enrollment;
        enrollment["studentId"] = e.studentId;
        enrollment["courseId"] = e.courseId;
        data["enrollments"].push_back(enrollment);
    }
    
    //   saver for grades
    data["grades"] = json::array();
    for (auto& g : grades) {
        json grade;
        grade["studentId"] = g.studentId;
        grade["courseId"] = g.courseId;
        grade["score"] = g.score;
        grade["note"] = g.note;
        grade["teacherId"] = g.teacherId;
        data["grades"].push_back(grade);
    }
    
    ofstream file(dataFile);
    file << data.dump(4);
    file.close();
}

//   initializer with sample data
void DataStore::initializeDefaultData() {
    //   adder for teachers (each teaches ONE course)
    users.push_back({"T001", "mrsmith", "teacher123", "teacher", "Mr. Smith", "Mr", "Smith", "", "mrsmith@school.edu"});
    users.push_back({"T002", "msjones", "teacher123", "teacher", "Ms. Jones", "Ms", "Jones", "", "msjones@school.edu"});
    users.push_back({"T003", "mrwilson", "teacher123", "teacher", "Mr. Wilson", "Mr", "Wilson", "", "mrwilson@school.edu"});
    users.push_back({"T004", "msdavis", "teacher123", "teacher", "Ms. Davis", "Ms", "Davis", "", "msdavis@school.edu"});
    
    //   adder for students (IDs auto-generated from first letter of first/last name)
    users.push_back({"JD001", "john", "john123", "student", "John Doe", "John", "Doe", "2005-03-15", "john@school.edu"});
    users.push_back({"JS001", "jane", "jane123", "student", "Jane Smith", "Jane", "Smith", "2005-07-22", "jane@school.edu"});
    users.push_back({"BJ001", "bob", "bob123", "student", "Bob Johnson", "Bob", "Johnson", "2005-11-08", "bob@school.edu"});
    
    //   adder for courses (each course has ONE teacher)
    courses.push_back({"C001", "Mathematics", "T001", "Algebra, Calculus, and Geometry"});
    courses.push_back({"C002", "English", "T002", "Literature, Grammar, and Writing"});
    courses.push_back({"C003", "Science", "T003", "Physics, Chemistry, and Biology"});
    courses.push_back({"C004", "History", "T004", "World History and Civics"});
    courses.push_back({"C005", "Computer Science", "T001", "Programming and Web Development"});
    
    //   adder for enrollments (students can enroll in MANY courses)
    enrollments.push_back({"JD001", "C001"});
    enrollments.push_back({"JD001", "C002"});
    enrollments.push_back({"JD001", "C005"});
    
    enrollments.push_back({"JS001", "C001"});
    enrollments.push_back({"JS001", "C002"});
    enrollments.push_back({"JS001", "C003"});
    
    enrollments.push_back({"BJ001", "C001"});
    enrollments.push_back({"BJ001", "C004"});
    
    //   adder for sample grades (linked to courses)
    grades.push_back({"JD001", "C001", 85, "Good progress", "T001"});
    grades.push_back({"JD001", "C002", 90, "Excellent work", "T002"});
    grades.push_back({"JD001", "C005", 95, "Outstanding!", "T001"});
    
    grades.push_back({"JS001", "C001", 78, "Needs improvement", "T001"});
    grades.push_back({"JS001", "C002", 88, "Very good", "T002"});
    grades.push_back({"JS001", "C003", 82, "Good effort", "T003"});
    
    grades.push_back({"BJ001", "C001", 92, "Outstanding", "T001"});
    grades.push_back({"BJ001", "C004", 85, "Solid work", "T004"});
    
    saveData();
}

//   authenticator for user
User* DataStore::authenticateUser(string username, string password) {
    for (auto& user : users) {
        if (user.username == username && user.password == password) {
            return &user;
        }
    }
    return nullptr;
}

//   adder for new user
void DataStore::addUser(User user) {
    users.push_back(user);
    saveData();
}

//   counter for teachers
int DataStore::getTeacherCount() {
    int count = 0;
    for (auto& user : users) {
        if (user.role == "teacher") {
            count++;
        }
    }
    return count;
}

//   counter for students
int DataStore::getStudentCount() {
    int count = 0;
    for (auto& user : users) {
        if (user.role == "student") {
            count++;
        }
    }
    return count;
}

//   assigner for teacher to course
void DataStore::assignTeacherToCourse(string teacherId, string courseId) {
    for (auto& course : courses) {
        if (course.id == courseId) {
            course.teacherId = teacherId;
            saveData();
            return;
        }
    }
}

//   enroller for student in course
void DataStore::enrollStudent(string studentId, string courseId) {
    // checker to prevent duplicate enrollments
    for (auto& enrollment : enrollments) {
        if (enrollment.studentId == studentId && enrollment.courseId == courseId) {
            return; // already enrolled
        }
    }
    
    // adder for new enrollment
    Enrollment newEnrollment;
    newEnrollment.studentId = studentId;
    newEnrollment.courseId = courseId;
    enrollments.push_back(newEnrollment);
    saveData();
}

//   getter for user by ID
User* DataStore::getUserById(string userId) {
    for (auto& user : users) {
        if (user.id == userId) {
            return &user;
        }
    }
    return nullptr;
}

//   getter for all students
vector<User> DataStore::getAllStudents() {
    vector<User> students;
    for (auto& user : users) {
        if (user.role == "student") {
            students.push_back(user);
        }
    }
    return students;
}

//   getter for grades for a student
vector<Grade> DataStore::getGradesByStudent(string studentId) {
    vector<Grade> studentGrades;
    for (auto& grade : grades) {
        if (grade.studentId == studentId) {
            studentGrades.push_back(grade);
        }
    }
    return studentGrades;
}

//   getter for all courses
vector<Course> DataStore::getAllCourses() {
    return courses;
}

//   getter for course by ID
Course* DataStore::getCourseById(string courseId) {
    for (auto& course : courses) {
        if (course.id == courseId) {
            return &course;
        }
    }
    return nullptr;
}

//   getter for courses for a specific teacher
vector<Course> DataStore::getCoursesByTeacher(string teacherId) {
    vector<Course> teacherCourses;
    for (auto& course : courses) {
        if (course.teacherId == teacherId) {
            teacherCourses.push_back(course);
        }
    }
    return teacherCourses;
}

//   getter for enrolled courses for a student
vector<Course> DataStore::getEnrolledCourses(string studentId) {
    vector<Course> studentCourses;
    for (auto& enrollment : enrollments) {
        if (enrollment.studentId == studentId) {
            Course* course = getCourseById(enrollment.courseId);
            if (course != nullptr) {
                studentCourses.push_back(*course);
            }
        }
    }
    return studentCourses;
}

//   checker if student is enrolled in a course
bool DataStore::isEnrolled(string studentId, string courseId) {
    for (auto& enrollment : enrollments) {
        if (enrollment.studentId == studentId && enrollment.courseId == courseId) {
            return true;
        }
    }
    return false;
}

//   enroller for student in a course
void DataStore::enrollStudent(string studentId, string courseId) {
    if (!isEnrolled(studentId, courseId)) {
        enrollments.push_back({studentId, courseId});
        saveData();
    }
}

//   unenroller for student from a course
void DataStore::unenrollStudent(string studentId, string courseId) {
    for (auto it = enrollments.begin(); it != enrollments.end(); ++it) {
        if (it->studentId == studentId && it->courseId == courseId) {
            enrollments.erase(it);
            saveData();
            return;
        }
    }
}

//   getter for students enrolled in a course
vector<User> DataStore::getStudentsByCourse(string courseId) {
    vector<User> enrolledStudents;
    for (auto& enrollment : enrollments) {
        if (enrollment.courseId == courseId) {
            for (auto& user : users) {
                if (user.id == enrollment.studentId && user.role == "student") {
                    enrolledStudents.push_back(user);
                    break;
                }
            }
        }
    }
    return enrolledStudents;
}

//   getter for all grades (for teacher)
vector<Grade> DataStore::getAllGrades() {
    return grades;
}

//   getter for grades for a teacher's courses
vector<Grade> DataStore::getGradesByTeacher(string teacherId) {
    vector<Grade> teacherGrades;
    for (auto& grade : grades) {
        if (grade.teacherId == teacherId) {
            teacherGrades.push_back(grade);
        }
    }
    return teacherGrades;
}

//   add or update grade
void DataStore::addOrUpdateGrade(string studentId, string courseId, int score, string note, string teacherId) {
    //   check if grade exists
    for (auto& grade : grades) {
        if (grade.studentId == studentId && grade.courseId == courseId) {
            grade.score = score;
            grade.note = note;
            grade.teacherId = teacherId;
            saveData();
            return;
        }
    }
    
    //   adding new grade
    grades.push_back({studentId, courseId, score, note, teacherId});
    saveData();
}

//   deleting grade
void DataStore::deleteGrade(string studentId, string courseId) {
    for (auto it = grades.begin(); it != grades.end(); ++it) {
        if (it->studentId == studentId && it->courseId == courseId) {
            grades.erase(it);
            saveData();
            return;
        }
    }
}
