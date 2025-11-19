# School Management System - Backend

A simple REST API server built with C++ for managing students, teachers, notes, and grades.

## Features

- 🔐 Authentication API (Login)
- 👨‍🏫 Teacher endpoints (manage grades and students)
- 👨‍🎓 Student endpoints (view personal grades)
- 💾 JSON-based data persistence
- 🌐 CORS-enabled for frontend integration

## Prerequisites

- C++ compiler (g++ or clang++)
- Make (optional, for easier compilation)
- curl (for downloading dependencies)

## Setup Instructions

### 1. Download JSON Library

The backend uses [nlohmann/json](https://github.com/nlohmann/json) for JSON parsing. Download it:

```bash
curl -o json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp
```

Or use the Makefile (it downloads automatically):

```bash
make
```

### 2. Compile the Server

**Using Make:**
```bash
make
```

**Manual Compilation:**
```bash
g++ -std=c++17 -o school_server main.cpp
```

### 3. Run the Server

```bash
./school_server
```

The server will start on `http://localhost:8080`

## Default Credentials

### Teacher Account
- **Username:** `teacher`
- **Password:** `teacher123`

### Student Accounts
- **Username:** `john` | **Password:** `john123`
- **Username:** `jane` | **Password:** `jane123`
- **Username:** `bob` | **Password:** `bob123`

## API Endpoints

### Authentication

#### POST `/api/login`
Login with username and password.

**Request:**
```json
{
  "username": "teacher",
  "password": "teacher123"
}
```

**Response:**
```json
{
  "success": true,
  "user": {
    "id": "T001",
    "username": "teacher",
    "role": "teacher"
  }
}
```

### Teacher Endpoints

#### GET `/api/students`
Get list of all students.

**Response:**
```json
[
  {
    "id": "S001",
    "username": "john"
  }
]
```

#### GET `/api/grades`
Get all grades for all students.

**Response:**
```json
[
  {
    "studentId": "S001",
    "subject": "Mathematics",
    "score": 85,
    "note": "Good progress",
    "updatedBy": "T001"
  }
]
```

#### POST `/api/grades`
Add or update a grade.

**Request:**
```json
{
  "studentId": "S001",
  "subject": "Mathematics",
  "score": 90,
  "note": "Excellent improvement",
  "teacherId": "T001"
}
```

#### DELETE `/api/grades`
Delete a grade.

**Request:**
```json
{
  "studentId": "S001",
  "subject": "Mathematics"
}
```

### Student Endpoints

#### GET `/api/grades/{studentId}`
Get grades for a specific student.

**Example:** `/api/grades/S001`

**Response:**
```json
[
  {
    "subject": "Mathematics",
    "score": 85,
    "note": "Good progress"
  }
]
```

## Data Storage

Data is stored in `data.json` in the same directory as the executable. The file is created automatically with sample data on first run.

## Development

### Clean Build
```bash
make clean
make
```

### Reset Data
Delete `data.json` and restart the server to reset to default data:
```bash
rm data.json
./school_server
```

## Architecture

- **Simple HTTP Server**: Built using native sockets (POSIX)
- **Request Routing**: Pattern matching on HTTP method and path
- **Data Persistence**: JSON file storage
- **CORS Enabled**: Allows cross-origin requests from frontend

## Notes

- This is a simple educational project
- Not production-ready (no SSL, limited security, single-threaded)
- Suitable for local development and learning purposes
