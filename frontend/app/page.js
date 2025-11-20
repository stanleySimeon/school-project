'use client';

//   login and signup page for authentication for teachers and students

import { useState, useEffect } from 'react';
import { useRouter } from 'next/navigation';
import { login, signup, getAllCourses } from '@/lib/api';

export default function LoginPage() {
  const router = useRouter();
  const [isSignup, setIsSignup] = useState(false);
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [firstName, setFirstName] = useState('');
  const [lastName, setLastName] = useState('');
  const [dateOfBirth, setDateOfBirth] = useState('');
  const [email, setEmail] = useState('');
  const [courseId, setCourseId] = useState('');
  const [courses, setCourses] = useState([]);
  const [role, setRole] = useState('student'); //   role state: 'teacher' or 'student'
  const [error, setError] = useState('');
  const [loading, setLoading] = useState(false);

  //   fetcher for courses when signup is selected
  useEffect(() => {
    if (isSignup) {
      fetchCourses();
    }
  }, [isSignup]);

  //   fetcher for available courses
  const fetchCourses = async () => {
    try {
      const response = await getAllCourses();
      setCourses(response);
    } catch (err) {
      console.error('Failed to fetch courses:', err);
    }
  };

  //   handler for login form submission
  const handleLogin = async (e) => {
    e.preventDefault();
    setError('');
    setLoading(true);

    try {
      const response = await login(username, password);

      if (response.success && response.user) {
        //   verification that role matches selection
        if (response.user.role !== role) {
          setError(`Invalid credentials for ${role} account`);
          setLoading(false);
          return;
        }

        //   storage of user data in localStorage
        localStorage.setItem('user', JSON.stringify(response.user));

        //   redirect to appropriate dashboard
        if (response.user.role === 'teacher') {
          router.push('/teacher');
        } else {
          router.push('/student');
        }
      } else {
        setError(response.message || 'Invalid credentials');
      }
    } catch (err) {
      setError('Failed to connect to server. Please ensure the backend is running.');
      console.error('Login error:', err);
    } finally {
      setLoading(false);
    }
  };

  //   handler for signup form submission
  const handleSignup = async (e) => {
    e.preventDefault();
    setError('');
    setLoading(true);

    //   validation for course selection (only for teachers)
    if (role === 'teacher' && !courseId) {
      setError('Please select a course to teach');
      setLoading(false);
      return;
    }

    try {
      const signupData = {
        username,
        password,
        firstName,
        lastName,
        dateOfBirth,
        email,
        role
      };

      // Only include courseId for teachers
      if (role === 'teacher' && courseId) {
        signupData.courseId = courseId;
      }

      const response = await signup(signupData);

      if (response.success) {
        //   storage of user data in localStorage
        localStorage.setItem('user', JSON.stringify(response.user));

        //   redirect to appropriate dashboard
        if (response.user.role === 'teacher') {
          router.push('/teacher');
        } else {
          router.push('/student');
        }
      } else {
        setError(response.message || 'Failed to create account');
      }
    } catch (err) {
      setError('Failed to connect to server. Please ensure the backend is running.');
      console.error('Signup error:', err);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="min-h-screen flex items-center justify-center bg-gradient-to-br from-blue-500 to-purple-600 px-4 py-8">
      <div className="bg-white rounded-lg shadow-2xl p-4 sm:p-8 w-full max-w-md">
        {/* Header */}
        <div className="text-center mb-6 sm:mb-8">
          <h1 className="text-2xl sm:text-4xl font-bold text-gray-900 mb-2 sm:mb-4">
            School Management
          </h1>
          <p className="text-gray-600">{isSignup ? 'Create your account' : 'Sign in to your account'}</p>
        </div>

        {/* Login/Signup Form */}
        <form onSubmit={isSignup ? handleSignup : handleLogin} className="space-y-4 sm:space-y-6">
          {/* Role Selection */}
          <div>
            <label className="block text-sm font-medium text-gray-700 mb-3">
              I am a:
            </label>
            <div className="grid grid-cols-2 gap-3">
              <button
                type="button"
                onClick={() => setRole('student')}
                className={`py-3 px-4 rounded-lg font-semibold transition-all ${role === 'student'
                  ? 'bg-blue-600 text-white shadow-lg scale-105'
                  : 'bg-gray-100 text-gray-700 hover:bg-gray-200'
                  }`}
              >
                Student
              </button>
              <button
                type="button"
                onClick={() => setRole('teacher')}
                className={`py-3 px-4 rounded-lg font-semibold transition-all ${role === 'teacher'
                  ? 'bg-purple-600 text-white shadow-lg scale-105'
                  : 'bg-gray-100 text-gray-700 hover:bg-gray-200'
                  }`}
              >
                Teacher
              </button>
            </div>
          </div>

          {/* Signup Fields */}
          {isSignup && (
            <>
              {/* First Name */}
              <div>
                <label htmlFor="firstName" className="block text-sm font-medium text-gray-700 mb-2">
                  First Name
                </label>
                <input
                  id="firstName"
                  type="text"
                  value={firstName}
                  onChange={(e) => setFirstName(e.target.value)}
                  className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-transparent outline-none transition text-gray-900"
                  placeholder="Enter your first name"
                  required
                />
              </div>

              {/* Last Name */}
              <div>
                <label htmlFor="lastName" className="block text-sm font-medium text-gray-700 mb-2">
                  Last Name
                </label>
                <input
                  id="lastName"
                  type="text"
                  value={lastName}
                  onChange={(e) => setLastName(e.target.value)}
                  className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-transparent outline-none transition text-gray-900"
                  placeholder="Enter your last name"
                  required
                />
              </div>

              {/* Date of Birth */}
              <div>
                <label htmlFor="dateOfBirth" className="block text-sm font-medium text-gray-700 mb-2">
                  Date of Birth
                </label>
                <input
                  id="dateOfBirth"
                  type="date"
                  value={dateOfBirth}
                  onChange={(e) => setDateOfBirth(e.target.value)}
                  className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-transparent outline-none transition text-gray-900"
                  required
                />
              </div>

              {/* Email */}
              <div>
                <label htmlFor="email" className="block text-sm font-medium text-gray-700 mb-2">
                  Email
                </label>
                <input
                  id="email"
                  type="email"
                  value={email}
                  onChange={(e) => setEmail(e.target.value)}
                  className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-transparent outline-none transition text-gray-900"
                  placeholder="Enter your email"
                  required
                />
              </div>

              {/* Course Selection - Only for Teachers */}
              {role === 'teacher' && (
                <div>
                  <label htmlFor="course" className="block text-sm font-medium text-gray-700 mb-2">
                    Course to Teach
                  </label>
                  <select
                    id="course"
                    value={courseId}
                    onChange={(e) => setCourseId(e.target.value)}
                    className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-transparent outline-none transition text-gray-900"
                    required
                  >
                    <option value="">Select a course</option>
                    {courses.map((course) => (
                      <option key={course.id} value={course.id}>
                        {course.name}
                      </option>
                    ))}
                  </select>
                </div>
              )}
            </>
          )}

          {/* Username Input */}
          <div>
            <label htmlFor="username" className="block text-sm font-medium text-gray-700 mb-2">
              Username
            </label>
            <input
              id="username"
              type="text"
              value={username}
              onChange={(e) => setUsername(e.target.value)}
              className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-transparent outline-none transition text-gray-900"
              placeholder="Enter your username"
              required
            />
          </div>

          {/* Password Input */}
          <div>
            <label htmlFor="password" className="block text-sm font-medium text-gray-700 mb-2">
              Password
            </label>
            <input
              id="password"
              type="password"
              value={password}
              onChange={(e) => setPassword(e.target.value)}
              className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-transparent outline-none transition text-gray-900"
              placeholder="Enter your password"
              required
            />
          </div>

          {/* Error Message */}
          {error && (
            <div className="bg-red-50 border border-red-200 text-red-700 px-4 py-3 rounded-lg">
              {error}
            </div>
          )}

          {/* Submit Button */}
          <button
            type="submit"
            disabled={loading}
            className="w-full bg-blue-600 hover:bg-blue-700 text-white font-semibold py-3 rounded-lg transition duration-200 disabled:opacity-50 disabled:cursor-not-allowed"
          >
            {loading ? (isSignup ? 'Creating account...' : 'Signing in...') : (isSignup ? 'Sign Up' : 'Sign In')}
          </button>
        </form>

        {/* Toggle Sign Up/Sign In */}
        <div className="mt-4 text-center">
          <button
            onClick={() => {
              setIsSignup(!isSignup);
              setError('');
            }}
            className="text-blue-600 hover:text-blue-800 font-medium text-sm"
          >
            {isSignup ? 'Already have an account? Sign In' : "Don't have an account? Sign Up"}
          </button>
        </div>

        {/* Demo Credentials - Only show on login */}
        {!isSignup && (
          <div className="mt-6 sm:mt-8 p-3 sm:p-4 bg-gray-50 rounded-lg">
            <p className="text-sm font-semibold text-gray-700 mb-2">Demo Credentials:</p>
            <div className="text-sm text-gray-600 space-y-2">
              <div>
                <p className="font-medium text-purple-600">Teachers:</p>
                <p className="ml-2">mrsmith, msjones, mrwilson, msdavis</p>
                <p className="ml-2 text-xs">Password: teacher123</p>
              </div>
              <div>
                <p className="font-medium text-blue-600">Students:</p>
                <p className="ml-2">john, jane, bob</p>
                <p className="ml-2 text-xs">Passwords: john123, jane123, bob123</p>
              </div>
            </div>
          </div>
        )}
      </div>
    </div>
  );
}
