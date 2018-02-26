ExternalProject_Add(
  gsl
  GIT_REPOSITORY      https://github.com/Microsoft/GSL
  CMAKE_ARGS          "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external;-DCMAKE_CXX_FLAGS=-Wno-error=sign-conversion;-DCMAKE_BUILD_TYPE=Release;-DGSL_TEST=false"
  PREFIX              ${CMAKE_BINARY_DIR}/external/gsl/prefix
  TMP_DIR             ${CMAKE_BINARY_DIR}/external/gsl/tmp
  STAMP_DIR           ${CMAKE_BINARY_DIR}/external/gsl/stamp
  DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/gsl/download
  SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/gsl/src
  BINARY_DIR          ${CMAKE_BINARY_DIR}/external/gsl/build
  )

set(LIB_NAME libcm)
add_library(${LIB_NAME} STATIC
  "${CMAKE_CURRENT_SOURCE_DIR}/pimpl.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/allocator.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/pimpl.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/allocator.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/entity.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/entity.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/unit.h"
  )

add_library(Cm::lib ALIAS ${LIB_NAME})
target_compile_features(${LIB_NAME}
  PUBLIC cxx_std_17
  PRIVATE cxx_lambdas cxx_nullptr)
target_include_directories(${LIB_NAME} SYSTEM
  PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/external/include>)
target_include_directories(${LIB_NAME}
  PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:/include>)
target_compile_options(${LIB_NAME} PRIVATE $<$<CXX_COMPILER_ID:Clang>:-Weverything -Wno-c++98-compat>)
target_compile_options(${LIB_NAME} PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wpedantic -Wextra -Wall -Wno-c++98-compat>)
add_dependencies(${LIB_NAME} gsl)
