// this a API client module for communicating with the backend

const API_BASE_URL = 'https://schoolstudentmanagement-production.up.railway.app';

//   API functions

//   login user with username and password
export async function login(username, password) {
  const response = await fetch(`${API_BASE_URL}/api/login`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({ username, password }),
  });

  return response.json();
}

//   getter for all students (Teacher only)
export async function getAllStudents() {
  const response = await fetch(`${API_BASE_URL}/api/students`, {
    method: 'GET',
  });

  return response.json();
}

//   getter for all grades (Teacher only)
export async function getAllGrades() {
  const response = await fetch(`${API_BASE_URL}/api/grades`, {
    method: 'GET',
  });

  return response.json();
}

//   getter for grades for a specific student
export async function getStudentGrades(studentId) {
  const response = await fetch(`${API_BASE_URL}/api/grades/${studentId}`, {
    method: 'GET',
  });

  return response.json();
}

//   getter for all available courses
export async function getAllCourses() {
  const response = await fetch(`${API_BASE_URL}/api/courses`, {
    method: 'GET',
  });

  return response.json();
}

//   getter for courses enrolled by a student
export async function getStudentCourses(studentId) {
  const response = await fetch(`${API_BASE_URL}/api/students/${studentId}/courses`, {
    method: 'GET',
  });

  return response.json();
}

//   getter for enrolled students for a specific course
export async function getCourseStudents(courseId) {
  const response = await fetch(`${API_BASE_URL}/api/courses/${courseId}/students`, {
    method: 'GET',
  });

  return response.json();
}

//   enroller for a student in a course
export async function enrollCourse(studentId, courseId) {
  const response = await fetch(`${API_BASE_URL}/api/enroll`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({ studentId, courseId }),
  });

  return response.json();
}

// for a student from a course
export async function unenrollCourse(studentId, courseId) {
  const response = await fetch(`${API_BASE_URL}/api/unenroll`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({ studentId, courseId }),
  });

  return response.json();
}

//   getter for grades for a teacher (their courses only)
export async function getTeacherGrades(teacherId) {
  const response = await fetch(`${API_BASE_URL}/api/teacher/${teacherId}/grades`, {
    method: 'GET',
  });

  return response.json();
}

//   adder or updater for a grade (Teacher only)
export async function addOrUpdateGrade(studentId, courseId, score, note, teacherId) {
  const response = await fetch(`${API_BASE_URL}/api/grades`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({ studentId, courseId, score, note, teacherId }),
  });

  return response.json();
}

//   deleter for a grade (Teacher only)
export async function deleteGrade(studentId, courseId) {
  const response = await fetch(`${API_BASE_URL}/api/grades`, {
    method: 'DELETE',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({ studentId, courseId }),
  });

  return response.json();
}
