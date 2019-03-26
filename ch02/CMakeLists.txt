cmake_minimum_required(VERSION 2.8)

project(HelloSLAM)

add_executable(helloSLAM helloSLAM.cpp)

#create static library: libhello.a
add_library(hello libHelloSLAM.cpp)

#create shared library: libhello_share.so
add_library(hello_shared SHARED libHelloSLAM.cpp)

#simple app use the just created shared library
add_executable(useHello useHello.cpp)
target_link_libraries(useHello hello_shared)
