cmake_minimum_required(VERSION 3.2)
project(Tutorial VERSION 1.0.0.0 LANGUAGES CXX C)

include(ExternalProject)
find_package(Git REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR}/external/lib/cmake)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-format-style=file;-checks=*;-p=./;-enable-check-profile")
set (CMAKE_LINK_WHAT_YOU_USE TRUE)

add_subdirectory(src)
# add_subdirectory(test)
add_subdirectory(bench)

add_executable(cm ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(cm Cm::lib)
