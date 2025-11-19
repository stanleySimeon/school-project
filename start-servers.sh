#!/bin/bash

# this a script for starting both backend and frontend servers

echo "=========================================="
echo "School Management System - Server Startup"
echo "=========================================="

# this a getter for local IP address
LOCAL_IP=$(ifconfig | grep "inet " | grep -v 127.0.0.1 | awk '{print $2}' | head -n 1)

echo "Starting Backend Server..."
cd backend
./school_server &
BACKEND_PID=$!

sleep 2

echo "Starting Frontend Server..."
cd ../frontend
npm run dev -- -p 3001 &
FRONTEND_PID=$!

echo ""
echo "=========================================="
echo "Servers are running!"
echo "=========================================="
echo "Backend:  http://localhost:8080"
echo "Frontend: http://localhost:3001"
echo ""
echo "Network Access (share with teachers):"
echo "Backend:  http://${LOCAL_IP}:8080"
echo "Frontend: http://${LOCAL_IP}:3001"
echo "=========================================="
echo ""
echo "Press Ctrl+C to stop both servers"

# this a waiter for interrupt signal
trap "kill $BACKEND_PID $FRONTEND_PID; exit" INT
wait
