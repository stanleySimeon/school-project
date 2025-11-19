# 🎓 School Management System

A simple and elegant school management system with separate dashboards for teachers and students. Teachers can manage grades and notes, while students can view their personal academic information.

## Features

### 👨‍🏫 Teacher Dashboard
- View all students and their grades
- Add, update, and delete grades
- Add notes for each grade
- Manage multiple subjects

### 👨‍🎓 Student Dashboard
- View personal grades and notes
- See performance statistics
- Track average scores
- View teacher comments

### 🔐 Authentication
- Secure login system
- Role-based access control
- Session management

## Tech Stack

- **Backend**: C++ with REST API
- **Frontend**: Next.js 15 with TypeScript
- **Styling**: Tailwind CSS
- **Data Storage**: JSON file-based storage

## Project Structure

```
school-project/
├── backend/           # C++ REST API server
│   ├── main.cpp      # Main server file
│   ├── json.hpp      # JSON library
│   ├── Makefile      # Build automation
│   └── README.md     # Backend documentation
├── frontend/         # Next.js frontend
│   ├── app/          # App router pages
│   │   ├── page.tsx  # Login page
│   │   ├── teacher/  # Teacher dashboard
│   │   └── student/  # Student dashboard
│   ├── lib/          # Utilities and API
│   │   ├── api.ts    # API functions
│   │   └── types.ts  # TypeScript types
│   └── ...
└── README.md         # This file
```

## Quick Start

### Prerequisites

- **C++ compiler** (g++ or clang++)
- **Node.js** 18+ and npm
- **curl** (for downloading dependencies)

### 1. Backend Setup

```bash
cd backend

# Download JSON library
make download_json

# Compile the server
make

# Run the backend server
./school_server
```

The backend will start on `http://localhost:8080`

### 2. Frontend Setup

```bash
cd frontend

# Install dependencies
npm install

# Start the development server
npm run dev
```

The frontend will start on `http://localhost:3000`

## Default Login Credentials

### Teacher Account
- **Username**: `teacher`
- **Password**: `teacher123`

### Student Accounts
- **Username**: `john` | **Password**: `john123`
- **Username**: `jane` | **Password**: `jane123`
- **Username**: `bob` | **Password**: `bob123`

## Usage Guide

1. **Start the Backend**: First, run the C++ backend server in one terminal
2. **Start the Frontend**: Then, run the Next.js frontend in another terminal
3. **Login**: Open `http://localhost:3000` and login with one of the default credentials
4. **Explore**: 
   - As a teacher: Add, edit, and delete grades
   - As a student: View your grades and performance stats

## API Endpoints

### Authentication
- `POST /api/login` - Login with username and password

### Teacher Endpoints
- `GET /api/students` - Get all students
- `GET /api/grades` - Get all grades
- `POST /api/grades` - Add or update a grade
- `DELETE /api/grades` - Delete a grade

### Student Endpoints
- `GET /api/grades/{studentId}` - Get grades for a specific student

## Development

### Backend Development

```bash
cd backend

# Rebuild
make clean
make

# Reset data
rm data.json
./school_server
```

### Frontend Development

```bash
cd frontend

# Run development server with hot reload
npm run dev

# Build for production
npm run build

# Run production build
npm start
```

## Features Highlight

- ✅ Clean and modern UI with Tailwind CSS
- ✅ Responsive design for mobile and desktop
- ✅ Real-time data updates
- ✅ Role-based authentication
- ✅ Color-coded grade indicators
- ✅ Performance statistics for students
- ✅ Easy-to-use grade management for teachers
- ✅ Well-commented and readable code

## Notes

- This is a basic educational project
- Data is stored in a JSON file (`data.json`)
- The backend is single-threaded (one request at a time)
- No SSL/HTTPS (use only for local development)
- Simple authentication (not production-ready)

## License

This project is for educational purposes. Feel free to use and modify as needed.

## Support

For issues or questions, please check the individual README files in the `backend/` and `frontend/` directories.
