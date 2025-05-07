cmake_minimum_required(VERSION 3.10)

# Project name
project(zmq1)

# C++ standard
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# sudo apt install libzmq3-dev
# sudo apt install cppzmq-dev
# in /usr/lib/x86_64-linux-gnu/
# vcpkg install cppzmq

# or see https://github.com/zeromq/cppzmq
# Build steps:

# Build libzmq via cmake. This does an out of source build and installs the build files

# git clone https://github.com/zeromq/libzmq.git
# cd libzmq
# mkdir build
# cd build
# cmake ..
# sudo make -j4 install
# Build cppzmq via cmake. This does an out of source build and installs the build files

# git clone https://github.com/zeromq/cppzmq.git
# cd cppzmq
# mkdir build
# cd build
# cmake .. or cmake -DCPPZMQ_BUILD_TESTS=OFF .. to skip building tests
# sudo make -j4 install

if(WIN32)
    find_package(cppzmq CONFIG REQUIRED)
    message(STATUS "cppzmq lib = ${cppzmq}")
elseif(UNIX)
    # find_library(ZMQ_LIB libzmq.so)
    # message(STATUS "ZMQ_LIB lib = ${ZMQ_LIB}")
    find_package(cppzmq)
    message(STATUS "cppzmq lib = ${cppzmq}")
endif()

# Add the executables
add_executable(server server.cpp)
add_executable(client client.cpp)

if(WIN32)
    # target_link_libraries(server PRIVATE cppzmq cppzmq-static)
    # target_link_libraries(client PRIVATE cppzmq cppzmq-static)
    target_link_libraries(server cppzmq)
    target_link_libraries(client cppzmq)
elseif(UNIX)
    # target_link_libraries(server ${ZMQ_LIB})    
    # target_link_libraries(client ${ZMQ_LIB})
    target_link_libraries(server cppzmq)    
    target_link_libraries(client cppzmq)
endif()


