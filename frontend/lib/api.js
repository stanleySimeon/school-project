// ============================================================================
// API CONFIGURATION
// ============================================================================

export const API_BASE_URL = process.env.NEXT_PUBLIC_API_URL || 'http://localhost:8080';

// ============================================================================
// API FUNCTIONS
// ============================================================================

/**
 * Login user with username and password
 */
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

/**
 * Get all students (Teacher only)
 */
export async function getAllStudents() {
  const response = await fetch(`${API_BASE_URL}/api/students`, {
    method: 'GET',
  });
  
  return response.json();
}

/**
 * Get all grades (Teacher only)
 */
export async function getAllGrades() {
  const response = await fetch(`${API_BASE_URL}/api/grades`, {
    method: 'GET',
  });
  
  return response.json();
}

/**
 * Get grades for a specific student
 */
export async function getStudentGrades(studentId) {
  const response = await fetch(`${API_BASE_URL}/api/grades/${studentId}`, {
    method: 'GET',
  });
  
  return response.json();
}

/**
 * Add or update a grade (Teacher only)
 */
export async function addOrUpdateGrade(studentId, subject, score, note, teacherId) {
  const response = await fetch(`${API_BASE_URL}/api/grades`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({ studentId, subject, score, note, teacherId }),
  });
  
  return response.json();
}

/**
 * Delete a grade (Teacher only)
 */
export async function deleteGrade(studentId, subject) {
  const response = await fetch(`${API_BASE_URL}/api/grades`, {
    method: 'DELETE',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({ studentId, subject }),
  });
  
  return response.json();
}
