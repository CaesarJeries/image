cmake_minimum_required (VERSION 3.18.4)

project(image)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(image image.cpp image_test.cpp)
include_directories("$ENV{GIT_TOP}/cpp/utils")
