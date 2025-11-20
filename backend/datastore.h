#ifndef DATASTORE_H
#define DATASTORE_H

#include <vector>
#include <fstream>
#include "json.hpp"
#include "models.h"

using json = nlohmann::json;
using namespace std;

//   data storage section - manages users, courses, enrollments, and grades with JSON persistence

class DataStore {
private:
    vector<User> users;
    vector<Course> courses;
    vector<Enrollment> enrollments;
    vector<Grade> grades;
    string dataFile = "data.json";

public:
    DataStore();
    
    // data from JSON file
    void loadData();
    
    // data to JSON file
    void saveData();
    
    // initializer with sample data
    void initializeDefaultData();
    
    // authenticator for user
    User* authenticateUser(string username, string password);
    
    // adder for new user
    void addUser(User user);
    
    // counter for teachers
    int getTeacherCount();
    
    // counter for students
    int getStudentCount();
    
    // assigner for teacher to course
    void assignTeacherToCourse(string teacherId, string courseId);
    
    // enroller for student in course
    void enrollStudent(string studentId, string courseId);
    
    //  get user by ID
    User* getUserById(string userId);
    
    // all students
    vector<User> getAllStudents();
    
    // grades for a student
    vector<Grade> getGradesByStudent(string studentId);
    
    // all courses
    vector<Course> getAllCourses();
    
    //  get course by ID
    Course* getCourseById(string courseId);
    
    // courses for a specific teacher
    vector<Course> getCoursesByTeacher(string teacherId);
    
    // enrolled courses for a student
    vector<Course> getEnrolledCourses(string studentId);
    
    // checker if student is enrolled in a course
    bool isEnrolled(string studentId, string courseId);
    
    // unenroll for student from a course
    void unenrollStudent(string studentId, string courseId);
    
    // students enrolled in a course
    vector<User> getStudentsByCourse(string courseId);
    
    // all grades (for teacher)
    vector<Grade> getAllGrades();
    
    // grades for a teacher's courses
    vector<Grade> getGradesByTeacher(string teacherId);
    
    // adding or updating grade
    void addOrUpdateGrade(string studentId, string courseId, int score, string note, string teacherId);
    
    // deleting grade
    void deleteGrade(string studentId, string courseId);
};

#endif // DATASTORE_H
