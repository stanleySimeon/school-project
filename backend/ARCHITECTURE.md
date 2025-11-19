# Backend Architecture

The backend has been refactored from a monolithic 826-line `main.cpp` into a modular, maintainable architecture.

## Module Structure

### 1. models.h (Data Structures)
- **Purpose**: Defines core data structures
- **Contents**:
  - `User` struct (id, username, password, role, name)
  - `Course` struct (id, name, teacherId, description)
  - `Enrollment` struct (studentId, courseId)
  - `Grade` struct (studentId, courseId, score, note, teacherId)

### 2. datastore.h / datastore.cpp (Data Management)
- **Purpose**: Manages all data persistence and CRUD operations
- **Key Methods**:
  - Data persistence: `loadData()`, `saveData()`, `initializeDefaultData()`
  - Authentication: `authenticateUser()`
  - User operations: `getAllStudents()`, `getUserById()`
  - Course operations: `getAllCourses()`, `getCourseById()`
  - Enrollment operations: `enrollStudent()`, `unenrollStudent()`, `isEnrolled()`
  - Grade operations: `addOrUpdateGrade()`, `deleteGrade()`, `getGradesByStudent()`, `getGradesByTeacher()`
- **Lines**: ~340 lines

### 3. http.h / http.cpp (HTTP Utilities)
- **Purpose**: Handles HTTP request/response parsing and building
- **Contents**:
  - `HttpRequest` struct (method, path, headers, body)
  - `parseHttpRequest()`: Parses raw HTTP requests
  - `buildHttpResponse()`: Builds HTTP responses with CORS headers

### 4. handlers.h / handlers.cpp (API Handlers)
- **Purpose**: Implements business logic for each API endpoint
- **Handler Functions**:
  - `handleLogin()`: User authentication
  - `handleGetStudents()`: List all students
  - `handleGetCourses()`: List all courses
  - `handleGetStudentCourses()`: Get enrolled courses for a student
  - `handleEnrollCourse()`: Enroll student in course
  - `handleUnenrollCourse()`: Unenroll student from course
  - `handleGetTeacherGrades()`: Get all grades for teacher's courses
  - `handleGetStudentGrades()`: Get grades for a student
  - `handleGetCourseStudents()`: Get enrolled students for a course
  - `handleAddGrade()`: Add or update a grade
  - `handleDeleteGrade()`: Delete a grade
- **Lines**: ~210 lines

### 5. router.h / router.cpp (Request Routing)
- **Purpose**: Routes incoming HTTP requests to appropriate handlers
- **Function**: `routeRequest()`
- **Endpoints**:
  - `POST /api/login` → handleLogin
  - `GET /api/courses` → handleGetCourses
  - `GET /api/students` → handleGetStudents
  - `GET /api/students/{id}/courses` → handleGetStudentCourses
  - `GET /api/courses/{id}/students` → handleGetCourseStudents
  - `GET /api/grades/{studentId}` → handleGetStudentGrades
  - `GET /api/teacher/{teacherId}/grades` → handleGetTeacherGrades
  - `POST /api/enroll` → handleEnrollCourse
  - `POST /api/unenroll` → handleUnenrollCourse
  - `POST /api/grades` → handleAddGrade
  - `DELETE /api/grades` → handleDeleteGrade
- **Lines**: ~80 lines

### 6. main.cpp (Server Entry Point)
- **Purpose**: Server initialization and main loop
- **Contents**:
  - Socket creation and configuration
  - Server binding on port 8080
  - Connection accept loop
  - Request/response handling
- **Lines**: ~100 lines

## Build System

### Makefile
Compiles all modules and links them together:
```makefile
SOURCES = main.cpp datastore.cpp http.cpp handlers.cpp router.cpp
```

**Build Commands**:
- `make` - Compile the server
- `make clean` - Remove all build artifacts
- `make run` - Compile and run the server

## Benefits of Modular Architecture

1. **Separation of Concerns**: Each module has a single, well-defined responsibility
2. **Maintainability**: Changes to one module don't affect others
3. **Readability**: Files are smaller and easier to understand
4. **Testability**: Individual modules can be tested independently
5. **Reusability**: Modules can be reused in other projects
6. **Collaboration**: Multiple developers can work on different modules simultaneously

## Code Statistics

| File | Lines | Purpose |
|------|-------|---------|
| models.h | ~40 | Data structures |
| datastore.h | ~50 | Data management interface |
| datastore.cpp | ~340 | Data management implementation |
| http.h | ~25 | HTTP utilities interface |
| http.cpp | ~60 | HTTP parsing/response |
| handlers.h | ~50 | Handler declarations |
| handlers.cpp | ~210 | Handler implementations |
| router.h | ~15 | Router interface |
| router.cpp | ~80 | Request routing |
| main.cpp | ~100 | Server main loop |
| **Total** | **~970** | **All modules** |

**Original**: 826 lines in single file  
**New**: ~970 lines across 10 files (includes proper spacing and headers)

## Comment Style

All code uses the standardized comment format:
```cpp
//   [description]
```
