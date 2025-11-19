'use client';

//   student dashboard for viewing courses, enrolling, and viewing grades

import { useState, useEffect } from 'react';
import { useRouter } from 'next/navigation';
import { getStudentGrades, getAllCourses, getStudentCourses, enrollCourse, unenrollCourse } from '@/lib/api';

export default function StudentDashboard() {
  const router = useRouter();
  const [user, setUser] = useState(null);
  const [grades, setGrades] = useState([]);
  const [enrolledCourses, setEnrolledCourses] = useState([]);
  const [allCourses, setAllCourses] = useState([]);
  const [loading, setLoading] = useState(true);
  const [activeTab, setActiveTab] = useState('grades'); //   active tab state: 'grades' or 'courses'te: 'grades' or 'courses'

  //   loader for user and data on mount
  useEffect(() => {
    const userData = localStorage.getItem('user');
    if (!userData) {
      router.push('/');
      return;
    }

    const parsedUser = JSON.parse(userData);
    if (parsedUser.role !== 'student') {
      router.push('/');
      return;
    }

    setUser(parsedUser);
    loadData(parsedUser.id);
  }, [router]);

  //   loader for all student data
  const loadData = async (studentId) => {
    try {
      const [gradesData, coursesData, allCoursesData] = await Promise.all([
        getStudentGrades(studentId),
        getStudentCourses(studentId),
        getAllCourses()
      ]);
      setGrades(gradesData);
      setEnrolledCourses(coursesData);
      setAllCourses(allCoursesData);
    } catch (error) {
      console.error('Failed to load data:', error);
    } finally {
      setLoading(false);
    }
  };

  //   handler for course enrollment
  const handleEnroll = async (courseId) => {
    try {
      await enrollCourse(user.id, courseId);
      await loadData(user.id);
    } catch (error) {
      console.error('Failed to enroll:', error);
      alert('Failed to enroll in course');
    }
  };

  //   handler for course unenrollment
  const handleUnenroll = async (courseId) => {
    if (!confirm('Are you sure you want to drop this course?')) return;
    try {
      await unenrollCourse(user.id, courseId);
      await loadData(user.id);
    } catch (error) {
      console.error('Failed to unenroll:', error);
      alert('Failed to drop course');
    }
  };

  //   handler for logout
  const handleLogout = () => {
    localStorage.removeItem('user');
    router.push('/');
  };

  //   calculator for average score
  const calculateAverage = () => {
    if (grades.length === 0) return 0;
    const total = grades.reduce((sum, grade) => sum + grade.score, 0);
    return Math.round(total / grades.length);
  };

  if (loading) {
    return (
      <div className="min-h-screen flex items-center justify-center">
        <div className="text-xl">Loading...</div>
      </div>
    );
  }

  const average = calculateAverage();

  return (
    <div className="min-h-screen bg-gray-50">
      {/* Header */}
      <header className="bg-white shadow">
        <div className="w-full nd:max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-4 flex justify-between items-start sm:items-center sm:gap-0">
          <div>
            <h1 className="text-xl sm:text-2xl font-bold text-gray-900">Student Dashboard</h1>
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
        {/* Tabs */}
        <div className="mb-6">
          <div className="border-b border-gray-200">
            <nav className="-mb-px flex space-x-4 sm:space-x-8 overflow-x-auto">
              <button
                onClick={() => setActiveTab('grades')}
                className={`py-4 px-1 border-b-2 font-medium text-xs sm:text-sm whitespace-nowrap ${activeTab === 'grades'
                  ? 'border-blue-500 text-blue-600'
                  : 'border-transparent text-gray-500 hover:text-gray-700 hover:border-gray-300'
                  }`}
              >
                My Grades
              </button>
              <button
                onClick={() => setActiveTab('courses')}
                className={`py-4 px-1 border-b-2 font-medium text-xs sm:text-sm whitespace-nowrap ${activeTab === 'courses'
                  ? 'border-blue-500 text-blue-600'
                  : 'border-transparent text-gray-500 hover:text-gray-700 hover:border-gray-300'
                  }`}
              >
                My Courses
              </button>
              <button
                onClick={() => setActiveTab('enroll')}
                className={`py-4 px-1 border-b-2 font-medium text-xs sm:text-sm whitespace-nowrap ${activeTab === 'enroll'
                  ? 'border-blue-500 text-blue-600'
                  : 'border-transparent text-gray-500 hover:text-gray-700 hover:border-gray-300'
                  }`}
              >
                Enroll in Courses
              </button>
            </nav>
          </div>
        </div>

        {/* Statistics Cards */}
        <div className="flex gap-4 md:gap-6 mb-8">
          <div className="flex-1 bg-white rounded-lg shadow-md p-4 md:p-6">
            <h3 className="text-xs md:text-sm font-medium text-gray-500 mb-2">My Courses</h3>
            <p className="text-2xl md:text-3xl font-bold text-blue-600">{enrolledCourses.length}</p>
          </div>

          <div className="flex-1 bg-white rounded-lg shadow-md p-4 md:p-6">
            <h3 className="text-xs md:text-sm font-medium text-gray-500 mb-2">Average Score</h3>
            <p className="text-2xl md:text-3xl font-bold text-purple-600">{average}%</p>
          </div>
        </div>

        {/* Content based on active tab */}
        {activeTab === 'grades' && (
          <div className="bg-white rounded-lg shadow-md overflow-hidden">
            <div className="px-6 py-4 border-b border-gray-200">
              <h2 className="text-xl font-bold text-gray-900">My Grades</h2>
            </div>
            <div className="overflow-x-auto">
              {grades.length === 0 ? (
                <div className="px-6 py-8 text-center text-gray-500">
                  <p className="text-lg">No grades available yet</p>
                  <p className="text-sm mt-2">Check back later for updates</p>
                </div>
              ) : (
                <table className="w-full">
                  <thead className="bg-gray-50">
                    <tr>
                      <th className="px-3 md:px-6 py-2 md:py-3 text-left text-[10px] md:text-xs font-medium text-gray-500 uppercase tracking-wider">
                        Course
                      </th>
                      <th className="px-3 md:px-6 py-2 md:py-3 text-left text-[10px] md:text-xs font-medium text-gray-500 uppercase tracking-wider">
                        Score
                      </th>
                      <th className="px-3 md:px-6 py-2 md:py-3 text-left text-[10px] md:text-xs font-medium text-gray-500 uppercase tracking-wider">
                        Teacher's Note
                      </th>
                      <th className="px-3 md:px-6 py-2 md:py-3 text-left text-[10px] md:text-xs font-medium text-gray-500 uppercase tracking-wider">
                        Status
                      </th>
                    </tr>
                  </thead>
                  <tbody className="bg-white divide-y divide-gray-200">
                    {grades.map((grade, index) => (
                      <tr key={index} className="hover:bg-gray-50">
                        <td className="px-3 md:px-6 py-3 md:py-4 whitespace-nowrap text-xs md:text-sm font-medium text-gray-900">
                          {grade.courseName}
                        </td>
                        <td className="px-3 md:px-6 py-3 md:py-4 whitespace-nowrap text-xs md:text-sm text-gray-900">
                          <span className={`px-2 md:px-3 py-1 rounded-full text-[10px] md:text-sm font-semibold ${grade.score >= 80 ? 'bg-green-100 text-green-800' :
                            grade.score >= 60 ? 'bg-yellow-100 text-yellow-800' :
                              'bg-red-100 text-red-800'
                            }`}>
                            {grade.score}
                          </span>
                        </td>
                        <td className="px-3 md:px-6 py-3 md:py-4 text-xs md:text-sm text-gray-900">
                          {grade.note}
                        </td>
                        <td className="px-3 md:px-6 py-3 md:py-4 whitespace-nowrap text-xs md:text-sm">
                          {grade.score >= 80 ? (
                            <span className="text-green-600 font-semibold">Excellent</span>
                          ) : grade.score >= 60 ? (
                            <span className="text-yellow-600 font-semibold">Good</span>
                          ) : (
                            <span className="text-red-600 font-semibold">Needs Work</span>
                          )}
                        </td>
                      </tr>
                    ))}
                  </tbody>
                </table>
              )}
            </div>
          </div>
        )}

        {/* My Courses Tab */}
        {activeTab === 'courses' && (
          <div className="bg-white rounded-lg shadow-md overflow-hidden">
            <div className="px-6 py-4 border-b border-gray-200">
              <h2 className="text-xl font-bold text-gray-900">My Enrolled Courses</h2>
            </div>
            <div className="p-6">
              {enrolledCourses.length === 0 ? (
                <div className="text-center text-gray-500 py-8">
                  <p className="text-lg">No courses enrolled yet</p>
                  <p className="text-sm mt-2">Go to "Enroll in Courses" to get started</p>
                </div>
              ) : (
                <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
                  {enrolledCourses.map((course) => (
                    <div key={course.id} className="border rounded-lg p-4 hover:shadow-md transition">
                      <div className="flex items-start justify-between mb-2">
                        <h3 className="text-lg font-bold text-gray-900">{course.name}</h3>
                        <span className="text-xs bg-blue-100 text-blue-800 px-2 py-1 rounded">{course.id}</span>
                      </div>
                      <p className="text-sm text-gray-600 mb-3">{course.description}</p>
                      <div className="flex items-center justify-between">
                        <div className="text-sm text-gray-700">
                          <span className="font-medium">Teacher:</span> {course.teacherName || course.teacherId}
                        </div>
                        <button
                          onClick={() => handleUnenroll(course.id)}
                          className="px-3 py-1 text-sm bg-red-100 text-red-700 hover:bg-red-200 rounded-lg transition"
                        >
                          Drop Course
                        </button>
                      </div>
                    </div>
                  ))}
                </div>
              )}
            </div>
          </div>
        )}

        {/* Enroll in Courses Tab */}
        {activeTab === 'enroll' && (
          <div className="bg-white rounded-lg shadow-md overflow-hidden">
            <div className="px-6 py-4 border-b border-gray-200">
              <h2 className="text-xl font-bold text-gray-900">Available Courses</h2>
            </div>
            <div className="p-6">
              <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
                {allCourses.map((course) => {
                  const isEnrolled = enrolledCourses.some(ec => ec.id === course.id);
                  return (
                    <div key={course.id} className={`border rounded-lg p-4 ${isEnrolled ? 'bg-gray-50' : 'hover:shadow-md'} transition`}>
                      <div className="flex items-start justify-between mb-2">
                        <h3 className="text-lg font-bold text-gray-900">{course.name}</h3>
                        <span className="text-xs bg-gray-200 text-gray-700 px-2 py-1 rounded">{course.id}</span>
                      </div>
                      <p className="text-sm text-gray-600 mb-3">{course.description}</p>
                      <div className="flex items-center justify-between">
                        <div className="text-sm text-gray-700">
                          <span className="font-medium">Teacher:</span> {course.teacherName || course.teacherId}
                        </div>
                        {isEnrolled ? (
                          <span className="px-3 py-1 text-sm bg-green-100 text-green-700 rounded-lg">
                            Enrolled
                          </span>
                        ) : (
                          <button
                            onClick={() => handleEnroll(course.id)}
                            className="px-3 py-1 text-sm bg-blue-600 text-white hover:bg-blue-700 rounded-lg transition"
                          >
                            Enroll
                          </button>
                        )}
                      </div>
                    </div>
                  );
                })}
              </div>
            </div>
          </div>
        )}
      </main>
    </div>
  );
}
