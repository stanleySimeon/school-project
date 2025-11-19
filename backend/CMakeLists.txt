cmake_minimum_required(VERSION 3.10)
project(SchoolManagementBackend)

set(CMAKE_CXX_STANDARD 17)

# Add the executable
add_executable(school_server main.cpp)

# Link libraries (pthread for networking)
target_link_libraries(school_server pthread)
