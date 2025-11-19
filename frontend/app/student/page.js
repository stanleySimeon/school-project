'use client';

// ============================================================================
// STUDENT DASHBOARD - View Personal Notes and Grades
// ============================================================================

import { useState, useEffect } from 'react';
import { useRouter } from 'next/navigation';
import { getStudentGrades } from '@/lib/api';

export default function StudentDashboard() {
  const router = useRouter();
  const [user, setUser] = useState(null);
  const [grades, setGrades] = useState([]);
  const [loading, setLoading] = useState(true);

  // Load user and grades on mount
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
    loadGrades(parsedUser.id);
  }, [router]);

  // Load student grades from API
  const loadGrades = async (studentId) => {
    try {
      const gradesData = await getStudentGrades(studentId);
      setGrades(gradesData);
    } catch (error) {
      console.error('Failed to load grades:', error);
    } finally {
      setLoading(false);
    }
  };

  // Handle logout
  const handleLogout = () => {
    localStorage.removeItem('user');
    router.push('/');
  };

  // Calculate average score
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
        <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-4 flex justify-between items-center">
          <div>
            <h1 className="text-2xl font-bold text-gray-900">👨‍🎓 Student Dashboard</h1>
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
        {/* Statistics Cards */}
        <div className="grid grid-cols-1 md:grid-cols-3 gap-6 mb-8">
          {/* Total Subjects */}
          <div className="bg-white rounded-lg shadow-md p-6">
            <div className="flex items-center">
              <div className="p-3 bg-blue-100 rounded-full">
                <span className="text-2xl">📚</span>
              </div>
              <div className="ml-4">
                <p className="text-sm font-medium text-gray-600">Total Subjects</p>
                <p className="text-2xl font-bold text-gray-900">{grades.length}</p>
              </div>
            </div>
          </div>

          {/* Average Score */}
          <div className="bg-white rounded-lg shadow-md p-6">
            <div className="flex items-center">
              <div className="p-3 bg-green-100 rounded-full">
                <span className="text-2xl">📊</span>
              </div>
              <div className="ml-4">
                <p className="text-sm font-medium text-gray-600">Average Score</p>
                <p className="text-2xl font-bold text-gray-900">{average}</p>
              </div>
            </div>
          </div>

          {/* Performance */}
          <div className="bg-white rounded-lg shadow-md p-6">
            <div className="flex items-center">
              <div className="p-3 bg-purple-100 rounded-full">
                <span className="text-2xl">
                  {average >= 80 ? '🌟' : average >= 60 ? '👍' : '📈'}
                </span>
              </div>
              <div className="ml-4">
                <p className="text-sm font-medium text-gray-600">Performance</p>
                <p className="text-2xl font-bold text-gray-900">
                  {average >= 80 ? 'Excellent' : average >= 60 ? 'Good' : 'Improving'}
                </p>
              </div>
            </div>
          </div>
        </div>

        {/* Grades Table */}
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
                    <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                      Subject
                    </th>
                    <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                      Score
                    </th>
                    <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                      Teacher's Note
                    </th>
                    <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                      Status
                    </th>
                  </tr>
                </thead>
                <tbody className="bg-white divide-y divide-gray-200">
                  {grades.map((grade, index) => (
                    <tr key={index} className="hover:bg-gray-50">
                      <td className="px-6 py-4 whitespace-nowrap text-sm font-medium text-gray-900">
                        {grade.subject}
                      </td>
                      <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-900">
                        <span className={`px-3 py-1 rounded-full font-semibold ${
                          grade.score >= 80 ? 'bg-green-100 text-green-800' :
                          grade.score >= 60 ? 'bg-yellow-100 text-yellow-800' :
                          'bg-red-100 text-red-800'
                        }`}>
                          {grade.score}
                        </span>
                      </td>
                      <td className="px-6 py-4 text-sm text-gray-900">
                        {grade.note}
                      </td>
                      <td className="px-6 py-4 whitespace-nowrap text-sm">
                        {grade.score >= 80 ? (
                          <span className="text-green-600 font-semibold">✓ Excellent</span>
                        ) : grade.score >= 60 ? (
                          <span className="text-yellow-600 font-semibold">○ Good</span>
                        ) : (
                          <span className="text-red-600 font-semibold">! Needs Work</span>
                        )}
                      </td>
                    </tr>
                  ))}
                </tbody>
              </table>
            )}
          </div>
        </div>
      </main>
    </div>
  );
}
