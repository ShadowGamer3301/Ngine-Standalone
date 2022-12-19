cmake_minimum_required(VERSION 3.12)

#Add project definitions
project(Ngine VERSION 1.0)

#Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(Ngine SHARED "src/Exception.cxx" "src/Window.cxx"  "src/Timer.cxx")

target_include_directories(Ngine PRIVATE "include")
target_link_libraries(Ngine PRIVATE "libglfw.so")
