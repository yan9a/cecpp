cmake_minimum_required(VERSION 3.10.0)
project(MyPb VERSION 0.1.0 LANGUAGES C CXX)

find_package(Protobuf REQUIRED)
set(PROTO_FILES MyMes.proto)
set(GENERATED_DIR ${CMAKE_BINARY_DIR})
file(MAKE_DIRECTORY ${GENERATED_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

add_executable(MyPb mymes.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(MyPb PUBLIC ${Protobuf_INCLUDE_DIRS} ${GENERATED_DIR})
target_link_libraries(MyPb PUBLIC protobuf::libprotobuf)

message(STATUS "PROTO_SRCS = ${PROTO_SRCS}")
message(STATUS "PROTO_HDRS = ${PROTO_HDRS}")
message(STATUS "Protobuf_INCLUDE_DIRS = ${Protobuf_INCLUDE_DIRS}")
message(STATUS "GENERATED_DIR = ${GENERATED_DIR}")

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
