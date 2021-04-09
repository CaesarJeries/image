cmake_minimum_required (VERSION 3.18.4)

project(image)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# read the environment variable `GIT_TOP`
include_directories("$ENV{GIT_TOP}/cpp/utils")
include_directories("/usr/local/include/opencv4")

add_custom_target(draw
                  BYPRODUCTS draw
                  COMMAND g++ draw.cpp -o draw -lSDL2 -L. -limage -I$ENV{HOME}/git/cpp/utils -ldl -Wl,-rpath .
                  VERBATIM
                  DEPENDS draw.cpp libimage.so)

add_library(image SHARED image.cpp)

set(LIB_DEPS opencv_core opencv_highgui opencv_imgcodecs)

target_link_libraries(image ${LIB_DEPS})
