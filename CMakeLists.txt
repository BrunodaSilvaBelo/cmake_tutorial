cmake_minimum_required(VERSION 3.2)
project(Tutorial VERSION 1.0.0.0 LANGUAGES CXX C)

include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
  catch
  GIT_REPOSITORY      https://github.com/philsquared/Catch.git
  CMAKE_ARGS          "-DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/external;-DCMAKE_BUILD_TYPE=Release;-DNO_SELFTEST=true"
  PREFIX              ${PROJECT_BINARY_DIR}/external/catch/prefix
  TMP_DIR             ${PROJECT_BINARY_DIR}/external/catch/tmp
  STAMP_DIR           ${PROJECT_BINARY_DIR}/external/catch/stamp
  DOWNLOAD_DIR        ${PROJECT_BINARY_DIR}/external/catch/download
  SOURCE_DIR          ${PROJECT_BINARY_DIR}/external/catch/src
  BINARY_DIR          ${PROJECT_BINARY_DIR}/external/catch/build
  )

ExternalProject_Add(
  gsl
  GIT_REPOSITORY      https://github.com/Microsoft/GSL
  CMAKE_ARGS          "-DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/external;-DCMAKE_CXX_FLAGS=-Wno-error=sign-conversion;-DCMAKE_BUILD_TYPE=Release;-DGSL_TEST=false"
  PREFIX              ${PROJECT_BINARY_DIR}/external/gsl/prefix
  TMP_DIR             ${PROJECT_BINARY_DIR}/external/gsl/tmp
  STAMP_DIR           ${PROJECT_BINARY_DIR}/external/gsl/stamp
  DOWNLOAD_DIR        ${PROJECT_BINARY_DIR}/external/gsl/download
  SOURCE_DIR          ${PROJECT_BINARY_DIR}/external/gsl/src
  BINARY_DIR          ${PROJECT_BINARY_DIR}/external/gsl/build
  DEPENDS catch
  )



ExternalProject_ADD(coveralls
  GIT_REPOSITORY    https://github.com/JoakimSoderberg/coveralls-cmake.git
  PREFIX              ${PROJECT_BINARY_DIR}/external/coveralls/prefix
  TMP_DIR             ${PROJECT_BINARY_DIR}/external/coveralls/tmp
  STAMP_DIR           ${PROJECT_BINARY_DIR}/external/coveralls/stamp
  DOWNLOAD_DIR        ${PROJECT_BINARY_DIR}/external/coveralls/download
  SOURCE_DIR          ${PROJECT_BINARY_DIR}/external/coveralls/src
  BINARY_DIR          ${PROJECT_BINARY_DIR}/external/coveralls/build
  UPDATE_COMMAND      ${GIT_EXECUTABLE} pull
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  LOG_DOWNLOAD      ON
  )
ExternalProject_Get_Property(coveralls source_dir)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${source_dir}/cmake ${PROJECT_BINARY_DIR}/external/lib/cmake)

ExternalProject_Add(
  google-benchmark
  GIT_REPOSITORY      https://github.com/google/benchmark.git
  GIT_TAG             v1.3.0
  CMAKE_ARGS          "-DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/external;-DCMAKE_BUILD_TYPE=Release;-DBENCHMARK_ENABLE_TESTING=false"
  PREFIX              ${PROJECT_BINARY_DIR}/external/benchmark/prefix
  TMP_DIR             ${PROJECT_BINARY_DIR}/external/benchmark/tmp
  STAMP_DIR           ${PROJECT_BINARY_DIR}/external/benchmark/stamp
  DOWNLOAD_DIR        ${PROJECT_BINARY_DIR}/external/benchmark/download
  SOURCE_DIR          ${PROJECT_BINARY_DIR}/external/benchmark/src
  BINARY_DIR          ${PROJECT_BINARY_DIR}/external/benchmark/build
  )

set(LIB_NAME libcm)
add_library(${LIB_NAME} STATIC
  "${CMAKE_SOURCE_DIR}/src/pimpl.cpp"
  "${CMAKE_SOURCE_DIR}/src/allocator.cpp"
  "${CMAKE_SOURCE_DIR}/src/pimpl.h"
  "${CMAKE_SOURCE_DIR}/src/allocator.h"
  )
add_library(Cm::lib ALIAS ${LIB_NAME})

target_compile_features(${LIB_NAME}
  PUBLIC cxx_std_14
  PRIVATE cxx_lambdas cxx_nullptr)
target_include_directories(${LIB_NAME} SYSTEM
  PUBLIC $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/external/include>)
target_include_directories(${LIB_NAME}
  PUBLIC  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src> $<INSTALL_INTERFACE:/include>)
target_compile_options(${LIB_NAME} PRIVATE $<$<CXX_COMPILER_ID:Clang>:-pedantic -Weverything -Wno-c++98-compat>)
target_compile_options(${LIB_NAME} PRIVATE $<$<CXX_COMPILER_ID:GNU>:-pedantic -Wextra -Wall -Wno-c++98-compat>)

set(EXE_NAME cm)
add_executable(${EXE_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${EXE_NAME} Cm::lib)
add_dependencies(${LIB_NAME} gsl)

find_package(Threads REQUIRED)
add_executable(cm_bench ${PROJECT_SOURCE_DIR}/src/bench.cpp)
target_compile_features(cm_bench
  PUBLIC cxx_std_14)
target_include_directories(cm_bench
  PUBLIC $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/external/include>)
target_link_libraries(cm_bench ${PROJECT_BINARY_DIR}/external/lib/libbenchmark.a ${CMAKE_THREAD_LIBS_INIT})
add_dependencies(cm_bench google-benchmark)
