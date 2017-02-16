cmake_minimum_required(VERSION 3.3)
project(Server_Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES myFtpServer.cpp myFtpServer.h Socket.cpp Socket.h lib.cpp lib.h)
add_executable(Server_Client ${SOURCE_FILES})