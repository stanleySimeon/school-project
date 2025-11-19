#ifndef MODELS_H
#define MODELS_H

#include <string>
using namespace std;

//   data models section - define user, course, enrollment, and grade structures

struct User {
    string id;
    string username;
    string password;
    string role;
    string name;

struct Course {
    string id;
    string name;
    string teacherId;
    string description;
};

struct Enrollment {
    string studentId;
    string courseId;
};

struct Grade {
    string studentId;
    string courseId;
    int score;
    string note;
    string teacherId;
};

#endif // MODELS_H
