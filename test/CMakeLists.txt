ExternalProject_Add(
  catch
  GIT_REPOSITORY      https://github.com/philsquared/Catch.git
  CMAKE_ARGS          "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external;-DCMAKE_BUILD_TYPE=Release;-DNO_SELFTEST=true"
  PREFIX              ${CMAKE_BINARY_DIR}/external/catch/prefix
  TMP_DIR             ${CMAKE_BINARY_DIR}/external/catch/tmp
  STAMP_DIR           ${CMAKE_BINARY_DIR}/external/catch/stamp
  DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/catch/download
  SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/catch/src
  BINARY_DIR          ${CMAKE_BINARY_DIR}/external/catch/build
  )

ExternalProject_ADD(coveralls
  GIT_REPOSITORY    https://github.com/JoakimSoderberg/coveralls-cmake.git
  PREFIX              ${CMAKE_BINARY_DIR}/external/coveralls/prefix
  TMP_DIR             ${CMAKE_BINARY_DIR}/external/coveralls/tmp
  STAMP_DIR           ${CMAKE_BINARY_DIR}/external/coveralls/stamp
  DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/coveralls/download
  SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/coveralls/src
  BINARY_DIR          ${CMAKE_BINARY_DIR}/external/coveralls/build
  UPDATE_COMMAND      ${GIT_EXECUTABLE} pull
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  )
ExternalProject_Get_Property(coveralls source_dir)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${source_dir}/cmake)
