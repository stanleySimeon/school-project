#!/bin/bash

echo "=========================================="
echo "🎓 School Management System Setup"
echo "=========================================="
echo ""

# Check prerequisites
echo "Checking prerequisites..."

# Check for g++
if ! command -v g++ &> /dev/null; then
    echo "❌ g++ not found. Please install a C++ compiler."
    exit 1
fi
echo "✅ g++ found"

# Check for Node.js
if ! command -v node &> /dev/null; then
    echo "❌ Node.js not found. Please install Node.js 18+."
    exit 1
fi
echo "✅ Node.js found ($(node -v))"

# Check for npm
if ! command -v npm &> /dev/null; then
    echo "❌ npm not found. Please install npm."
    exit 1
fi
echo "✅ npm found ($(npm -v))"

echo ""
echo "=========================================="
echo "Setting up Backend..."
echo "=========================================="
cd backend

# Download JSON library
echo "Downloading nlohmann/json library..."
if [ ! -f json.hpp ] || grep -q "error" json.hpp; then
    curl -o json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp
    echo "✅ JSON library downloaded"
else
    echo "✅ JSON library already exists"
fi

# Compile backend
echo "Compiling backend server..."
make clean
make
if [ $? -eq 0 ]; then
    echo "✅ Backend compiled successfully"
else
    echo "❌ Backend compilation failed"
    exit 1
fi

cd ..

echo ""
echo "=========================================="
echo "Setting up Frontend..."
echo "=========================================="
cd frontend

# Install npm dependencies
if [ ! -d "node_modules" ]; then
    echo "Installing npm dependencies..."
    npm install
    if [ $? -eq 0 ]; then
        echo "✅ Frontend dependencies installed"
    else
        echo "❌ Frontend installation failed"
        exit 1
    fi
else
    echo "✅ Frontend dependencies already installed"
fi

cd ..

echo ""
echo "=========================================="
echo "✅ Setup Complete!"
echo "=========================================="
echo ""
echo "To run the application:"
echo ""
echo "1. Start Backend (Terminal 1):"
echo "   cd backend && ./school_server"
echo ""
echo "2. Start Frontend (Terminal 2):"
echo "   cd frontend && npm run dev"
echo ""
echo "3. Open http://localhost:3000 in your browser"
echo ""
echo "Default Credentials:"
echo "  Teacher: teacher / teacher123"
echo "  Student: john / john123"
echo ""
echo "=========================================="
