'use client';

//   teacher dashboard for managing courses and student grades

import { useState, useEffect } from 'react';
import { useRouter } from 'next/navigation';
import { getAllCourses, getTeacherGrades, addOrUpdateGrade, deleteGrade, getCourseStudents } from '@/lib/api';

export default function TeacherDashboard() {
  const router = useRouter();
  const [user, setUser] = useState(null);
  const [courses, setCourses] = useState([]);
  const [grades, setGrades] = useState([]);
  const [loading, setLoading] = useState(true);

  //   form state
  const [selectedCourse, setSelectedCourse] = useState('');
  const [selectedStudent, setSelectedStudent] = useState('');
  const [enrolledStudents, setEnrolledStudents] = useState([]);
  const [score, setScore] = useState('');
  const [note, setNote] = useState('');
  const [showForm, setShowForm] = useState(false);
  const [errorMessage, setErrorMessage] = useState('');

  //   loader for user and data on mount
  useEffect(() => {
    const userData = localStorage.getItem('user');
    if (!userData) {
      router.push('/');
      return;
    }

    const parsedUser = JSON.parse(userData);
    if (parsedUser.role !== 'teacher') {
      router.push('/');
      return;
    }

    setUser(parsedUser);
    loadData(parsedUser);
  }, [router]);

  //   loader for teacher courses and grades from API
  const loadData = async (teacherUser) => {
    const currentUser = teacherUser || user;
    if (!currentUser) return;

    try {
      const [coursesData, gradesData] = await Promise.all([
        getAllCourses(),
        getTeacherGrades(currentUser.id)
      ]);

      //   filter to only courses this teacher teaches
      const teacherCourses = coursesData.filter(c => c.teacherId === currentUser.id);
      setCourses(teacherCourses);
      setGrades(gradesData);
    } catch (error) {
      console.error('Failed to load data:', error);
    } finally {
      setLoading(false);
    }
  };

  //   handler for logout
  const handleLogout = () => {
    localStorage.removeItem('user');
    router.push('/');
  };

  //   loader for enrolled students when course is selected
  const handleCourseChange = async (courseId) => {
    setSelectedCourse(courseId);
    setSelectedStudent('');
    setErrorMessage('');

    if (courseId) {
      try {
        const students = await getCourseStudents(courseId);
        setEnrolledStudents(students);
        if (students.length === 0) {
          setErrorMessage('No students enrolled in this course yet');
        }
      } catch (error) {
        console.error('Failed to load students:', error);
        setEnrolledStudents([]);
      }
    } else {
      setEnrolledStudents([]);
    }
  };

  //   handler for form submission
  const handleSubmit = async (e) => {
    e.preventDefault();
    if (!user) return;

    setErrorMessage('');

    if (!selectedStudent) {
      setErrorMessage('Please select a student');
      return;
    }

    try {
      const response = await addOrUpdateGrade(
        selectedStudent,
        selectedCourse,
        parseInt(score),
        note,
        user.id
      );

      if (response.success === false) {
        setErrorMessage(response.message || 'Failed to add grade');
        return;
      }

      //   form reset
      setSelectedStudent('');
      setSelectedCourse('');
      setEnrolledStudents([]);
      setScore('');
      setNote('');
      setShowForm(false);

      //   data reload
      await loadData(user);
    } catch (error) {
      console.error('Failed to add grade:', error);
      setErrorMessage('Failed to add/update grade. Please try again.');
    }
  };

  //   handler for delete grade
  const handleDelete = async (studentId, courseId) => {
    const course = courses.find(c => c.id === courseId);
    if (!confirm(`Delete grade for this student in ${course?.name || 'course'}?`)) return;

    try {
      await deleteGrade(studentId, courseId);
      await loadData(user);
    } catch (error) {
      console.error('Failed to delete grade:', error);
      alert('Failed to delete grade');
    }
  };

  //    get course name by ID
  const getCourseName = (courseId) => {
    const course = courses.find(c => c.id === courseId);
    return course ? course.name : courseId;
  };

  //    get students enrolled in a specific course
  const getEnrolledStudents = (courseId) => {
    return grades
      .filter(g => g.courseId === courseId)
      .map(g => g.studentName)
      .filter((name, index, self) => self.indexOf(name) === index);
  };

  //    get unique students across all grades
  const getTotalStudents = () => {
    const uniqueStudents = grades
      .map(g => g.studentId)
      .filter((id, index, self) => self.indexOf(id) === index);
    return uniqueStudents.length;
  };

  if (loading) {
    return (
      <div className="min-h-screen flex items-center justify-center">
        <div className="text-xl">Loading...</div>
      </div>
    );
  }

  return (
    <div className="min-h-screen bg-gray-50">
      {/* Header */}
      <header className="bg-white shadow">
        <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-4 flex flex-col sm:flex-row justify-between items-start sm:items-center">
          <div>
            <h1 className="text-xl sm:text-2xl font-bold text-gray-900">Teacher Dashboard</h1>
            <p className="text-sm text-gray-600">Welcome, {user?.username}</p>
          </div>
          <button
            onClick={handleLogout}
            className="px-4 py-2 bg-red-600 hover:bg-red-700 text-white rounded-lg transition"
          >
            Logout
          </button>
        </div>
      </header>

      <main className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-8">
        {/* Stats */}
        <div className="flex gap-4 md:gap-6 mb-8">
          <div className="flex-1 bg-white rounded-lg shadow-md p-4 md:p-6">
            <h3 className="text-xs md:text-sm font-medium text-gray-500 mb-2">My Courses</h3>
            <p className="text-2xl md:text-3xl font-bold text-blue-600">{courses.length}</p>
          </div>
          <div className="flex-1 bg-white rounded-lg shadow-md p-4 md:p-6">
            <h3 className="text-xs md:text-sm font-medium text-gray-500 mb-2">Total Students</h3>
            <p className="text-2xl md:text-3xl font-bold text-green-600">{getTotalStudents()}</p>
          </div>
          <div className="flex-1 bg-white rounded-lg shadow-md p-4 md:p-6">
            <h3 className="text-xs md:text-sm font-medium text-gray-500 mb-2">Average Score</h3>
            <p className="text-2xl md:text-3xl font-bold text-purple-600">
              {grades.length > 0 ? Math.round(grades.reduce((sum, g) => sum + g.score, 0) / grades.length) : 0}%
            </p>
          </div>
        </div>

        {/* Add Grade Button */}
        <div className="mb-6">
          <button
            onClick={() => setShowForm(!showForm)}
            className="w-full sm:w-auto px-6 py-3 bg-blue-600 hover:bg-blue-700 text-white rounded-lg font-semibold transition">

            {showForm ? '✕ Cancel' : '+ Add Grade'}
          </button>
        </div>

        {/* Add/Edit Grade Form */}
        {showForm && (
          <div className="bg-white rounded-lg shadow-md p-4 sm:p-6 mb-8">
            <h2 className="text-lg sm:text-xl font-bold text-gray-900 mb-4">Add/Update Grade</h2>
            {errorMessage && (
              <div className="mb-4 bg-red-50 border border-red-200 text-red-700 px-4 py-3 rounded-lg">
                {errorMessage}
              </div>
            )}
            <form onSubmit={handleSubmit} className="grid grid-cols-1 md:grid-cols-2 gap-4">
              <div>
                <label className="block text-sm font-medium text-gray-700 mb-2">
                  Course
                </label>
                <select
                  value={selectedCourse}
                  onChange={(e) => handleCourseChange(e.target.value)}
                  className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 text-gray-900"
                  required
                >
                  <option value="">Select a course first</option>
                  {courses.map((course) => (
                    <option key={course.id} value={course.id}>
                      {course.name}
                    </option>
                  ))}
                </select>
              </div>

              <div>
                <label className="block text-sm font-medium text-gray-700 mb-2">
                  Student
                </label>
                <select
                  value={selectedStudent}
                  onChange={(e) => setSelectedStudent(e.target.value)}
                  className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 text-gray-900"
                  disabled={!selectedCourse || enrolledStudents.length === 0}
                  required
                >
                  <option value="">
                    {!selectedCourse ? 'Select a course first' :
                      enrolledStudents.length === 0 ? 'No enrolled students' :
                        'Select a student'}
                  </option>
                  {enrolledStudents.map((student) => (
                    <option key={student.id} value={student.id}>
                      {student.name || student.username} ({student.id})
                    </option>
                  ))}
                </select>
                {selectedCourse && enrolledStudents.length === 0 && (
                  <p className="mt-1 text-xs text-yellow-600">
                    Students must enroll in this course first
                  </p>
                )}
              </div>

              <div>
                <label className="block text-sm font-medium text-gray-700 mb-2">
                  Score (0-100)
                </label>
                <input
                  type="number"
                  min="0"
                  max="100"
                  value={score}
                  onChange={(e) => setScore(e.target.value)}
                  className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 text-gray-900"
                  placeholder="85"
                  required
                />
              </div>

              <div>
                <label className="block text-sm font-medium text-gray-700 mb-2">
                  Note
                </label>
                <input
                  type="text"
                  value={note}
                  onChange={(e) => setNote(e.target.value)}
                  className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 text-gray-900"
                  placeholder="Good progress"
                  required
                />
              </div>

              <div className="md:col-span-2">
                <button
                  type="submit"
                  className="w-full px-6 py-3 bg-green-600 hover:bg-green-700 text-white rounded-lg font-semibold transition"
                >
                  Save Grade
                </button>
              </div>
            </form>
          </div>
        )}

        {/* My Courses */}
        <div className="bg-white rounded-lg shadow-md p-4 sm:p-6 mb-8">
          <h2 className="text-lg sm:text-xl font-bold text-gray-900 mb-4">My Courses</h2>
          {courses.length === 0 ? (
            <p className="text-gray-500 text-center py-4">No courses assigned yet</p>
          ) : (
            <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-4">
              {courses.map((course) => (
                <div key={course.id} className="border border-gray-200 rounded-lg p-4 hover:shadow-md transition">
                  <h3 className="font-bold text-gray-900 mb-2">{course.name}</h3>
                  <p className="text-sm text-gray-600 mb-3">{course.description}</p>
                  <div className="text-xs text-gray-500">
                    <p>Course ID: {course.id}</p>
                    <p>Enrolled Students: {getEnrolledStudents(course.id).length}</p>
                  </div>
                </div>
              ))}
            </div>
          )}
        </div>

        {/* Grades Table */}
        <div className="bg-white rounded-lg shadow-md overflow-hidden">
          <div className="px-4 sm:px-6 py-4 border-b border-gray-200">
            <h2 className="text-lg sm:text-xl font-bold text-gray-900">Student Grades</h2>
          </div>
          <div className="overflow-x-auto">
            <table className="w-full">
              <thead className="bg-gray-50">
                <tr>
                  <th className="px-3 md:px-6 py-2 md:py-3 text-left text-[10px] md:text-xs font-medium text-gray-500 uppercase tracking-wider">
                    Student
                  </th>
                  <th className="hidden md:table-cell px-3 md:px-6 py-2 md:py-3 text-left text-[10px] md:text-xs font-medium text-gray-500 uppercase tracking-wider">
                    Course
                  </th>
                  <th className="px-3 md:px-6 py-2 md:py-3 text-left text-[10px] md:text-xs font-medium text-gray-500 uppercase tracking-wider">
                    Score
                  </th>
                  <th className="hidden sm:table-cell px-3 md:px-6 py-2 md:py-3 text-left text-[10px] md:text-xs font-medium text-gray-500 uppercase tracking-wider">
                    Note
                  </th>
                  <th className="px-3 md:px-6 py-2 md:py-3 text-left text-[10px] md:text-xs font-medium text-gray-500 uppercase tracking-wider">
                    Actions
                  </th>
                </tr>
              </thead>
              <tbody className="bg-white divide-y divide-gray-200">
                {grades.length === 0 ? (
                  <tr>
                    <td colSpan={5} className="px-6 py-4 text-center text-gray-500">
                      No grades added yet
                    </td>
                  </tr>
                ) : (
                  grades.map((grade, index) => (
                    <tr key={index} className="hover:bg-gray-50">
                      <td className="px-3 md:px-6 py-3 md:py-4 text-xs md:text-sm font-medium text-gray-900">
                        <div>{grade.studentName || grade.studentId}</div>
                        <div className="text-[10px] md:text-xs text-gray-500">{grade.studentId}</div>
                      </td>
                      <td className="hidden md:table-cell px-3 md:px-6 py-3 md:py-4 whitespace-nowrap text-xs md:text-sm text-gray-900">
                        {grade.courseName || getCourseName(grade.courseId)}
                      </td>
                      <td className="px-3 md:px-6 py-3 md:py-4 whitespace-nowrap text-xs md:text-sm text-gray-900">
                        <span className={`px-2 md:px-3 py-1 rounded-full font-semibold text-[10px] md:text-sm ${grade.score >= 80 ? 'bg-green-100 text-green-800' :
                          grade.score >= 60 ? 'bg-yellow-100 text-yellow-800' :
                            'bg-red-100 text-red-800'
                          }`}>
                          {grade.score}
                        </span>
                      </td>
                      <td className="hidden sm:table-cell px-3 md:px-6 py-3 md:py-4 text-xs md:text-sm text-gray-900">
                        {grade.note}
                      </td>
                      <td className="px-3 md:px-6 py-3 md:py-4 whitespace-nowrap text-[10px] md:text-sm">
                        <button
                          onClick={() => handleDelete(grade.studentId || '', grade.courseId)}
                          className="text-red-600 hover:text-red-800 font-medium"
                        >
                          Delete
                        </button>
                      </td>
                    </tr>
                  ))
                )}
              </tbody>
            </table>
          </div>
        </div>
      </main>
    </div>
  );
}
