cmake_minimum_required(VERSION 3.10)

# Project name
project(zmq1)

# # C++ standard
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# sudo apt-get install libzmq3-dev
# in /usr/lib/x86_64-linux-gnu/
# vcpkg install cppzmq

if(WIN32)
    find_package(cppzmq CONFIG REQUIRED)
elseif(UNIX)
    find_library(ZMQ_LIB libzmq.so)
    # find_package(ZeroMQ REQUIRED)
endif()

# Add the executables
add_executable(server server.cpp)
add_executable(client client.cpp)

if(WIN32)
    # target_link_libraries(server PRIVATE cppzmq cppzmq-static)
    # target_link_libraries(client PRIVATE cppzmq cppzmq-static)
    target_link_libraries(server PRIVATE cppzmq)
    target_link_libraries(client PRIVATE cppzmq)
elseif(UNIX)
    target_link_libraries(server ${ZMQ_LIB})    
    target_link_libraries(client ${ZMQ_LIB})
    # target_link_libraries(server PRIVATE libzmq)    
    # target_link_libraries(client PRIVATE libzmq)
endif()


