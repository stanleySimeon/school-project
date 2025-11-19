#ifndef HANDLERS_H
#define HANDLERS_H

#include <string>
#include "json.hpp"
#include "datastore.h"
#include "http.h"

using json = nlohmann::json;
using namespace std;

//   API handlers section - handle specific API endpoints

// login authentication
string handleLogin(DataStore& store, string body);

// signup new user
string handleSignup(DataStore& store, string body);

// list of all students
string handleGetStudents(DataStore& store);

// all courses
string handleGetCourses(DataStore& store);

// enrolled courses for a student
string handleGetStudentCourses(DataStore& store, string studentId);

// enroll for student in a course
string handleEnrollCourse(DataStore& store, string body);

// unenroll for student from a course
string handleUnenrollCourse(DataStore& store, string body);

// grades for all courses for teacher view
string handleGetTeacherGrades(DataStore& store, string teacherId);

// grades for a specific student with course info
string handleGetStudentGrades(DataStore& store, string studentId);

// enrolled students for a specific course
string handleGetCourseStudents(DataStore& store, string courseId);

// adding or updating a grade
string handleAddGrade(DataStore& store, string body);

// deleting a grade
string handleDeleteGrade(DataStore& store, string body);

#endif // HANDLERS_H
