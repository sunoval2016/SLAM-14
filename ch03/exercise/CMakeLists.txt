cmake_minimum_required(VERSION 2.8)
project(rbtPosition)

#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS "-std=c++11")

# add Eigen headers
include_directories("/usr/include/eigen3")

add_executable(rbtPosition rbtPosition.cpp)
