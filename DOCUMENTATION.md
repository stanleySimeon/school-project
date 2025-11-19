# School Management System - Complete Documentation

A modern, full-stack school management system for managing students, teachers, courses, enrollments, and grades.

## 📋 Table of Contents

1. [Overview](#overview)
2. [Features](#features)
3. [Technology Stack](#technology-stack)
4. [System Requirements](#system-requirements)
5. [Installation Guide](#installation-guide)
   - [Windows](#windows-installation)
   - [macOS](#macos-installation)
   - [Linux](#linux-installation)
6. [Running the Application](#running-the-application)
7. [User Guide](#user-guide)
8. [Project Structure](#project-structure)
9. [API Documentation](#api-documentation)
10. [Development](#development)
11. [Troubleshooting](#troubleshooting)

---

## Overview

This School Management System provides a comprehensive platform for teachers to manage courses and student grades, while allowing students to enroll in courses and view their academic progress. The system features a modern, responsive web interface with a robust backend API.

### Key Highlights

- **Role-Based Access**: Separate dashboards for teachers and students
- **Course Management**: Teachers can create and manage multiple courses
- **Grade Tracking**: Teachers assign grades; students view their performance
- **Enrollment System**: Students can enroll/unenroll from courses
- **Real-Time Statistics**: Dashboard metrics for performance monitoring
- **Responsive Design**: Works seamlessly on desktop, tablet, and mobile devices
- **Persistent Storage**: JSON-based data storage system

---

## Features

### For Teachers
- View all assigned courses
- Manage student enrollments
- Add, update, and delete grades
- View class statistics and average scores
- Filter students by course enrollment
- Track total students across all courses

### For Students
- View enrolled courses with teacher information
- Check grades and teacher feedback
- Enroll in available courses
- Unenroll from courses
- Track average performance
- View personalized statistics

### System Features
- Auto-generated student IDs (format: JD001, JS001, etc.)
- Course-based grade management
- Enrollment validation (only enrolled students can receive grades)
- Secure authentication system
- Data persistence across sessions
- RESTful API architecture

---

## Technology Stack

### Backend
- **Language**: C++17
- **HTTP Server**: Custom implementation using sockets
- **JSON Library**: nlohmann/json
- **Build System**: Make/CMake
- **Port**: 8080

### Frontend
- **Framework**: Next.js 16.0.3
- **React Version**: 19.2.0
- **Styling**: Tailwind CSS 4
- **Port**: 3001

### Data Storage
- **Format**: JSON file (`data.json`)
- **Location**: Backend directory

---

## System Requirements

### Windows

**Minimum Requirements:**
- Windows 10 or later (64-bit)
- 4 GB RAM
- 500 MB free disk space
- Internet connection (for initial setup)

**Software Requirements:**
- Git Bash or WSL2
- MinGW-w64 (GCC compiler) or Visual Studio 2019+
- Node.js 18.x or later
- npm 9.x or later

### macOS

**Minimum Requirements:**
- macOS 11 (Big Sur) or later
- 4 GB RAM
- 500 MB free disk space
- Internet connection (for initial setup)

**Software Requirements:**
- Xcode Command Line Tools
- Node.js 18.x or later
- npm 9.x or later

### Linux

**Minimum Requirements:**
- Ubuntu 20.04+ / Debian 11+ / Fedora 35+
- 4 GB RAM
- 500 MB free disk space
- Internet connection (for initial setup)

**Software Requirements:**
- GCC 9+ or Clang 10+
- Make
- Node.js 18.x or later
- npm 9.x or later

---

## Installation Guide

### Windows Installation

#### Step 1: Install Git
1. Download Git from [git-scm.com](https://git-scm.com/download/win)
2. Run installer and follow prompts
3. Select "Git Bash Here" during installation

#### Step 2: Install MinGW-w64 (C++ Compiler)

**Option A: Using MSYS2 (Recommended)**
1. Download MSYS2 from [msys2.org](https://www.msys2.org/)
2. Install MSYS2 to `C:\msys64`
3. Open MSYS2 terminal and run:
   ```bash
   pacman -Syu
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make
   ```
4. Add to PATH: `C:\msys64\mingw64\bin`

**Option B: Using MinGW-w64 Standalone**
1. Download from [sourceforge.net/projects/mingw-w64](https://sourceforge.net/projects/mingw-w64/)
2. Install and add bin folder to system PATH
3. Verify installation:
   ```bash
   gcc --version
   g++ --version
   ```

#### Step 3: Install Node.js
1. Download Node.js from [nodejs.org](https://nodejs.org/) (LTS version)
2. Run installer (includes npm automatically)
3. Verify installation:
   ```bash
   node --version
   npm --version
   ```

#### Step 4: Clone the Project
```bash
# Open Git Bash
cd Desktop
git clone <repository-url>
cd school-project
```

#### Step 5: Setup Backend
```bash
cd backend
make
```

**Note for Windows:** If `make` command not found:
```bash
# Using MSYS2 terminal
mingw32-make

# Or compile manually
g++ -std=c++17 -Wall -Wextra -o school_server main.cpp datastore.cpp http.cpp handlers.cpp router.cpp
```

#### Step 6: Setup Frontend
```bash
cd ../frontend
npm install
```

#### Step 7: Run the Application
Open **two separate terminals**:

**Terminal 1 - Backend:**
```bash
cd backend
./school_server.exe    # or just: school_server
```

**Terminal 2 - Frontend:**
```bash
cd frontend
npm run dev -- -p 3001
```

Access the application at: `http://localhost:3001`

---

### macOS Installation

#### Step 1: Install Xcode Command Line Tools
```bash
xcode-select --install
```

#### Step 2: Install Homebrew (Optional but Recommended)
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

#### Step 3: Install Node.js
```bash
# Using Homebrew
brew install node

# Or download from nodejs.org
```

#### Step 4: Clone the Project
```bash
cd ~/Desktop
git clone <repository-url>
cd school-project
```

#### Step 5: Setup Backend
```bash
cd backend
make
```

#### Step 6: Setup Frontend
```bash
cd ../frontend
npm install
```

#### Step 7: Run the Application
Open two terminal tabs:

**Tab 1 - Backend:**
```bash
cd backend
./school_server
```

**Tab 2 - Frontend:**
```bash
cd frontend
npm run dev -- -p 3001
```

Access at: `http://localhost:3001`

---

### Linux Installation

#### Step 1: Install Build Tools
```bash
# Ubuntu/Debian
sudo apt update
sudo apt install build-essential git curl

# Fedora
sudo dnf install gcc-c++ make git curl

# Arch
sudo pacman -S base-devel git curl
```

#### Step 2: Install Node.js
```bash
# Ubuntu/Debian
curl -fsSL https://deb.nodesource.com/setup_20.x | sudo -E bash -
sudo apt install -y nodejs

# Fedora
sudo dnf install nodejs npm

# Arch
sudo pacman -S nodejs npm
```

#### Step 3: Clone the Project
```bash
cd ~/Desktop
git clone <repository-url>
cd school-project
```

#### Step 4: Setup Backend
```bash
cd backend
make
```

#### Step 5: Setup Frontend
```bash
cd ../frontend
npm install
```

#### Step 6: Run the Application
Open two terminals:

**Terminal 1 - Backend:**
```bash
cd backend
./school_server
```

**Terminal 2 - Frontend:**
```bash
cd frontend
npm run dev -- -p 3001
```

Access at: `http://localhost:3001`

---

## Running the Application

### Quick Start Script (macOS/Linux)

We provide a convenience script to start both servers:

```bash
./start-servers.sh
```

This will:
- Start the backend server on port 8080
- Start the frontend server on port 3001
- Display local and network URLs
- Show default login credentials

### Manual Start

**Backend:**
```bash
cd backend
make                    # First time only
./school_server
```

**Frontend:**
```bash
cd frontend
npm run dev -- -p 3001
```

### Stopping the Application

Press `Ctrl+C` in each terminal to stop the servers.

To force kill if needed:
```bash
# Kill backend (port 8080)
lsof -ti:8080 | xargs kill -9

# Kill frontend (port 3001)
lsof -ti:3001 | xargs kill -9
```

On Windows:
```bash
# Find process using port
netstat -ano | findstr :8080
netstat -ano | findstr :3001

# Kill by PID
taskkill /PID <process_id> /F
```

---

## User Guide

### Login

Navigate to `http://localhost:3001`

**Default Teacher Accounts:**
- **Username:** `mrsmith` | **Password:** `teacher123` (Math & Computer Science)
- **Username:** `msjones` | **Password:** `teacher123` (English)
- **Username:** `mrwilson` | **Password:** `teacher123` (Science)
- **Username:** `msdavis` | **Password:** `teacher123` (History)

**Default Student Accounts:**
- **Username:** `john` | **Password:** `john123` (Student ID: JD001)
- **Username:** `jane` | **Password:** `jane123` (Student ID: JS001)
- **Username:** `bob` | **Password:** `bob123` (Student ID: BJ001)

### Teacher Dashboard

#### Viewing Statistics
The dashboard displays three key metrics:
- **My Courses**: Total courses you teach
- **Total Students**: Unique students across all your courses
- **Average Score**: Average grade across all your students

#### Adding a Grade
1. Click **"+ Add Grade"** button
2. Select a course from dropdown
3. Select a student (only enrolled students appear)
4. Enter score (0-100)
5. Add optional note/feedback
6. Click **"Add/Update Grade"**

#### Viewing Grades
- All grades displayed in a table
- Filter by student name or course
- Scores color-coded:
  - **Green**: 80+ (Excellent)
  - **Yellow**: 60-79 (Good)
  - **Red**: Below 60 (Needs Work)

#### Deleting a Grade
Click **"Delete"** button next to any grade entry.

#### Managing Courses
View your assigned courses with:
- Course name and description
- Course ID
- Number of enrolled students

### Student Dashboard

#### Viewing Statistics
- **My Courses**: Total enrolled courses
- **Total Students**: System-wide student count
- **Average Score**: Your average grade percentage

#### My Grades Tab
View all your grades with:
- Course name
- Score with status indicator
- Teacher's feedback notes
- Performance status

#### My Courses Tab
View enrolled courses showing:
- Course name and ID
- Teacher name
- Course description
- **Drop Course** button

#### Enroll in Courses Tab
Browse available courses:
- View all courses in the system
- See teacher information
- Click **"Enroll"** to join a course
- Already enrolled courses show "Enrolled" status

---

## Project Structure

```
school-project/
├── backend/                      # C++ Backend Server
│   ├── main.cpp                  # Server entry point
│   ├── models.h                  # Data structures (User, Course, Enrollment, Grade)
│   ├── datastore.h/.cpp          # Data management layer
│   ├── http.h/.cpp               # HTTP request/response handling
│   ├── handlers.h/.cpp           # API endpoint handlers
│   ├── router.h/.cpp             # Request routing
│   ├── json.hpp                  # JSON library (auto-downloaded)
│   ├── Makefile                  # Build configuration
│   ├── ARCHITECTURE.md           # Backend architecture documentation
│   └── data.json                 # Persistent data storage (created on first run)
│
├── frontend/                     # Next.js Frontend
│   ├── app/                      # Application pages
│   │   ├── page.js              # Login page
│   │   ├── layout.js            # Root layout
│   │   ├── globals.css          # Global styles
│   │   ├── teacher/
│   │   │   └── page.js          # Teacher dashboard
│   │   └── student/
│   │       └── page.js          # Student dashboard
│   ├── lib/
│   │   └── api.js               # API client functions
│   ├── public/                   # Static assets
│   ├── package.json              # Dependencies
│   ├── jsconfig.json             # Path aliases configuration
│   ├── postcss.config.js         # PostCSS configuration
│   └── next.config.js            # Next.js configuration
│
├── start-servers.sh              # Convenience script to start both servers
├── DEPLOYMENT.md                 # Deployment instructions
├── DOCUMENTATION.md              # This file
└── README.md                     # Project overview
```

### Backend Architecture

The backend follows a modular architecture:

1. **models.h**: Data structures for User, Course, Enrollment, and Grade
2. **datastore**: Manages all data operations and persistence
3. **http**: Handles HTTP protocol parsing and response building
4. **handlers**: Implements business logic for each API endpoint
5. **router**: Routes incoming requests to appropriate handlers
6. **main**: Initializes server and manages connections

---

## API Documentation

### Base URL
```
http://localhost:8080/api
```

### Authentication
Currently uses basic username/password authentication.

### Endpoints

#### POST `/api/login`
Authenticate a user.

**Request:**
```json
{
  "username": "john",
  "password": "john123"
}
```

**Response:**
```json
{
  "success": true,
  "user": {
    "id": "JD001",
    "username": "john",
    "role": "student"
  }
}
```

#### GET `/api/courses`
Get all courses with teacher information.

**Response:**
```json
[
  {
    "id": "C001",
    "name": "Mathematics",
    "teacherId": "T001",
    "teacherName": "mrsmith",
    "description": "Algebra, Calculus, and Geometry"
  }
]
```

#### GET `/api/students`
Get all students (teachers only).

**Response:**
```json
[
  {
    "id": "JD001",
    "username": "john"
  }
]
```

#### GET `/api/students/:studentId/courses`
Get enrolled courses for a student.

**Example:** `/api/students/JD001/courses`

#### GET `/api/courses/:courseId/students`
Get enrolled students for a course.

**Example:** `/api/courses/C001/students`

#### GET `/api/grades/:studentId`
Get grades for a student.

**Example:** `/api/grades/JD001`

**Response:**
```json
[
  {
    "courseId": "C001",
    "courseName": "Mathematics",
    "score": 95,
    "note": "Excellent work!",
    "teacherId": "T001"
  }
]
```

#### GET `/api/teacher/:teacherId/grades`
Get all grades for a teacher's courses.

**Example:** `/api/teacher/T001/grades`

#### POST `/api/enroll`
Enroll a student in a course.

**Request:**
```json
{
  "studentId": "JD001",
  "courseId": "C001"
}
```

#### POST `/api/unenroll`
Unenroll a student from a course.

**Request:**
```json
{
  "studentId": "JD001",
  "courseId": "C001"
}
```

#### POST `/api/grades`
Add or update a grade.

**Request:**
```json
{
  "studentId": "JD001",
  "courseId": "C001",
  "score": 95,
  "note": "Excellent work!",
  "teacherId": "T001"
}
```

**Response:**
```json
{
  "success": true,
  "message": "Grade added/updated successfully"
}
```

**Error (if student not enrolled):**
```json
{
  "success": false,
  "message": "Student is not enrolled in this course"
}
```

#### DELETE `/api/grades`
Delete a grade.

**Request:**
```json
{
  "studentId": "JD001",
  "courseId": "C001"
}
```

---

## Development

### Building the Backend

**Clean build:**
```bash
cd backend
make clean
make
```

**Development mode (auto-reload on changes):**
```bash
# Terminal 1: Watch and rebuild
cd backend
while true; do make; sleep 2; done

# Terminal 2: Run server
./school_server
```

### Frontend Development

**Development server with hot reload:**
```bash
cd frontend
npm run dev -- -p 3001
```

**Build for production:**
```bash
npm run build
npm start
```

**Linting:**
```bash
npm run lint
```

### Modifying Default Data

Edit `backend/datastore.cpp` in the `initializeDefaultData()` function:

```cpp
void DataStore::initializeDefaultData() {
    // Add your custom teachers
    users.push_back({"T005", "newteacher", "pass123", "teacher", "New Teacher"});
    
    // Add your custom students
    users.push_back({"NT001", "newstudent", "pass123", "student", "New Student"});
    
    // Add your custom courses
    courses.push_back({"C006", "New Course", "T005", "Description here"});
}
```

Then rebuild:
```bash
cd backend
rm data.json      # Delete existing data
make clean
make
./school_server
```

### Adding New API Endpoints

1. **Add handler in `handlers.h`:**
   ```cpp
   string handleNewFeature(DataStore& store, string body);
   ```

2. **Implement in `handlers.cpp`:**
   ```cpp
   string handleNewFeature(DataStore& store, string body) {
       // Your logic here
       return buildHttpResponse(200, "OK", response.dump());
   }
   ```

3. **Add route in `router.cpp`:**
   ```cpp
   if (req.method == "GET" && req.path == "/api/newfeature") {
       return handleNewFeature(store, req.body);
   }
   ```

4. **Add frontend API function in `lib/api.js`:**
   ```javascript
   export async function getNewFeature() {
       const response = await fetch(`${API_URL}/api/newfeature`);
       return response.json();
   }
   ```

---

## Troubleshooting

### Common Issues

#### Issue: "Port 8080 already in use"

**Solution:**
```bash
# macOS/Linux
lsof -ti:8080 | xargs kill -9

# Windows
netstat -ano | findstr :8080
taskkill /PID <process_id> /F
```

#### Issue: "Port 3001 already in use"

**Solution:**
```bash
# macOS/Linux
lsof -ti:3001 | xargs kill -9

# Windows
netstat -ano | findstr :3001
taskkill /PID <process_id> /F
```

#### Issue: "make: command not found" (Windows)

**Solution:**
Use `mingw32-make` instead:
```bash
mingw32-make
```

Or compile manually:
```bash
g++ -std=c++17 -Wall -Wextra -o school_server main.cpp datastore.cpp http.cpp handlers.cpp router.cpp
```

#### Issue: "Cannot find json.hpp"

**Solution:**
```bash
cd backend
make download_json
make
```

Or download manually:
```bash
curl -o json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp
```

#### Issue: Frontend shows "Module not found: Can't resolve '@/lib/api'"

**Solution:**
Ensure `jsconfig.json` exists in frontend folder:
```json
{
  "compilerOptions": {
    "baseUrl": ".",
    "paths": {
      "@/*": ["./*"]
    }
  }
}
```

#### Issue: "CORS error" when accessing API

**Cause:** Backend not running or wrong URL in frontend.

**Solution:**
1. Verify backend is running: `curl http://localhost:8080/api/courses`
2. Check `frontend/lib/api.js` has correct API_URL
3. CORS headers are already configured in `backend/http.cpp`

#### Issue: Styles not loading in frontend

**Solution:**
Ensure Tailwind CSS is properly configured:
```bash
cd frontend
npm install @tailwindcss/postcss tailwindcss
```

Check `postcss.config.js` exists:
```javascript
module.exports = {
  plugins: {
    '@tailwindcss/postcss': {},
  },
}
```

#### Issue: Data not persisting between server restarts

**Check:** `data.json` file should exist in backend folder after first run.

**Solution:** Verify file permissions:
```bash
chmod 644 backend/data.json
```

#### Issue: "error while loading shared libraries" (Linux)

**Solution:**
```bash
sudo ldconfig
```

#### Issue: Compilation errors about C++17

**Solution:**
Update GCC/Clang:
```bash
# Ubuntu
sudo apt install gcc-11 g++-11

# Set as default
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 100
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 100
```

### Getting Help

If you encounter issues not covered here:

1. Check the console output for error messages
2. Verify all prerequisites are installed
3. Try a clean rebuild:
   ```bash
   cd backend
   make clean
   make
   
   cd ../frontend
   rm -rf node_modules package-lock.json
   npm install
   ```
4. Check the GitHub issues page (if available)
5. Review the DEPLOYMENT.md for additional deployment options

---

## Performance Notes

### Expected Performance
- Backend can handle ~100 concurrent connections
- Frontend loads in under 2 seconds
- API response time: < 100ms for most operations
- Data file size: ~50KB for 100 students, 10 courses

### Optimization Tips
- Backend: Single-threaded; for production, consider multi-threading
- Frontend: Already uses Next.js SSR for optimal performance
- Database: For 1000+ students, consider migrating to PostgreSQL/MySQL

---

## Security Notes

**Important for Production Use:**

This is an educational project. For production deployment:

1. **Passwords:** Currently stored in plain text. Implement password hashing:
   ```cpp
   // Use bcrypt or similar
   #include <openssl/sha.h>
   ```

2. **Authentication:** Add JWT tokens instead of username/password
3. **Input Validation:** Add server-side validation for all inputs
4. **HTTPS:** Use SSL/TLS certificates
5. **Rate Limiting:** Prevent API abuse
6. **SQL Injection:** Not applicable (uses JSON), but validate all inputs

---

## Cloud Deployment

### Option 1: Railway + Vercel (Recommended)

#### Deploy Backend on Railway

**Using Web Interface (Easiest for Windows):**
1. Go to [railway.app](https://railway.app) and sign in with GitHub
2. Click **"New Project"** → **"Deploy from GitHub repo"**
3. Select your repository
4. Railway automatically detects the Dockerfile
5. Click **"Deploy"** and wait 2-3 minutes
6. Go to **Settings** → **Networking** → Copy your public URL
   - Example: `https://school-backend-production.up.railway.app`

**Using Railway CLI (Alternative):**
```bash
# Install Railway CLI
npm install -g @railway/cli

# Login
npx railway login

# Deploy
cd backend
npx railway up
```

#### Update Frontend API URL

1. Edit `frontend/lib/api.js`
2. Change line 3:
```javascript
const API_URL = 'https://your-railway-url.up.railway.app';
```

#### Deploy Frontend on Vercel

**Windows Users:**
```cmd
cd frontend
npx vercel
```

Follow prompts:
- Set up and deploy? **Y**
- Project name? **school-frontend**
- Directory? Press **Enter**
- Override settings? **N**

**After deployment:**
- Copy the Vercel URL
- Visit your app at the provided URL
- Share with teachers!

### Option 2: Render (All-in-One)

1. Go to [render.com](https://render.com) and sign in with GitHub
2. Click **"New +"** → **"Web Service"**
3. Connect your repository

**For Backend:**
- Environment: **Docker**
- Dockerfile path: `./backend/Dockerfile`
- Click **"Create Web Service"**

**For Frontend:**
- Environment: **Node**
- Build command: `cd frontend && npm install && npm run build`
- Start command: `cd frontend && npm start`
- Click **"Create Web Service"**

Wait 5-10 minutes for deployment to complete.

### Testing Deployment

Once deployed, test your endpoints:
```bash
# Test backend
curl https://your-backend-url.com/api/courses

# Should return JSON array of courses
```

### Sharing with Teachers

**Production URLs:**
- **Frontend**: `https://your-app.vercel.app`
- **Backend API**: `https://your-app.railway.app`

**Login Credentials:**
- Teachers: `mrsmith` / `teacher123`
- Students: `john` / `john123`

---

## Windows-Specific Notes

### PowerShell vs Command Prompt vs Git Bash

**Recommended: Git Bash** (comes with Git for Windows)
- Unix-like commands work
- Better compatibility with our scripts
- Most similar to macOS/Linux experience

**If using PowerShell:**
```powershell
# Instead of: make
mingw32-make

# Instead of: ./school_server
.\school_server.exe

# Instead of: rm -f file
Remove-Item file -Force
```

**If using Command Prompt:**
```cmd
REM Instead of: make
mingw32-make

REM Instead of: ./school_server
school_server.exe

REM Instead of: rm -f file
del /f file
```

### Common Windows Issues

#### Issue: "gcc not recognized"

**Solution:**
Add MinGW to PATH:
1. Press `Win + X` → **System**
2. **Advanced system settings** → **Environment Variables**
3. Under **System Variables**, find **Path**
4. Click **Edit** → **New**
5. Add: `C:\msys64\mingw64\bin` (or your MinGW path)
6. Click **OK** and restart terminal

#### Issue: "make not found"

**Solution 1 - Use mingw32-make:**
```bash
mingw32-make
```

**Solution 2 - Create alias in Git Bash:**
```bash
echo 'alias make="mingw32-make"' >> ~/.bashrc
source ~/.bashrc
```

**Solution 3 - Install Make separately:**
```bash
# Using chocolatey
choco install make

# Or download from: gnuwin32.sourceforge.net
```

#### Issue: Port already in use

**Windows Command:**
```cmd
# Find process using port 8080
netstat -ano | findstr :8080

# Kill process (replace PID with actual number)
taskkill /PID 12345 /F
```

**PowerShell:**
```powershell
# Find and kill process on port 8080
$port = 8080
Get-Process -Id (Get-NetTCPConnection -LocalPort $port).OwningProcess | Stop-Process -Force
```

#### Issue: Permission denied when running executables

**Solution:**
```bash
# Right-click school_server.exe
# Properties → Security → Edit
# Give your user "Full control"

# Or use icacls in cmd:
icacls school_server.exe /grant Everyone:F
```

### Windows Firewall

When running the server, Windows Firewall may ask for permission:
1. Click **"Allow access"** for both Private and Public networks
2. If you didn't see the prompt, manually add:
   - Control Panel → Windows Defender Firewall
   - Advanced settings → Inbound Rules → New Rule
   - Port → TCP → 8080 → Allow

### Windows Build Tips

**Fast Rebuild Script (save as `rebuild.bat`):**
```batch
@echo off
cd backend
mingw32-make clean
mingw32-make
echo Build complete!
pause
```

**Double-click to rebuild!**

---

## License

This project is provided as-is for educational purposes.

---

## Credits

Developed as a school management system demonstration project.

**Technologies Used:**
- C++17 with STL
- Next.js & React
- Tailwind CSS
- nlohmann/json library

---

## Version History

- **v1.0.0** - Initial release
  - Core functionality for teachers and students
  - Course and grade management
  - Responsive UI design
  - Modular backend architecture

---

For backend architecture details, see [backend/ARCHITECTURE.md](./backend/ARCHITECTURE.md)
