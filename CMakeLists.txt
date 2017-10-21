cmake_minimum_required(VERSION 3.2)
project(Tutorial VERSION 1.0.0.0 LANGUAGES CXX C)

include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
  catch
  GIT_REPOSITORY      https://github.com/philsquared/Catch.git
  GIT_TAG             master
  PREFIX "${CMAKE_SOURCE_DIR}/thirdparty/catch"
  DOWNLOAD_COMMAND    "git subtree add --prefix . https://github.com/philsquared/Catch.git master --squash"
  UPLOAD_COMMAND      "git subtree pull --prefix . https://github.com/philsquared/Catch.git master"
  )

# ExternalProject_ADD( coveralls
#   GIT_REPOSITORY https://github.com/JoakimSoderberg/coveralls-cmake.git
#   CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
#   PREFIX ${CMAKE_BINARY_DIR}/external/coveralls/prefix
#   TMP_DIR ${CMAKE_BINARY_DIR}/external/coveralls/tmp
#   STAMP_DIR ${CMAKE_BINARY_DIR}/external/coveralls/stamp
#   DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/external/coveralls/download
#   SOURCE_DIR ${CMAKE_BINARY_DIR}/external/coveralls/src
#   BINARY_DIR ${CMAKE_BINARY_DIR}/external/coveralls/build
#   )
