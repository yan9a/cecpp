cmake_minimum_required(VERSION 3.10)

# Project name
project(zmqthread)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(cppzmq)
# Add the executables
add_executable(zmqthread zmqthread.cpp)
target_link_libraries(zmqthread cppzmq)
