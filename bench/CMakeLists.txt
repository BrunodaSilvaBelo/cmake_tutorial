ExternalProject_Add(
  google-benchmark
  GIT_REPOSITORY      https://github.com/google/benchmark.git
  CMAKE_ARGS          "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external;-DCMAKE_BUILD_TYPE=Release;-DBENCHMARK_ENABLE_TESTING=false"
  PREFIX              ${CMAKE_BINARY_DIR}/external/benchmark/prefix
  TMP_DIR             ${CMAKE_BINARY_DIR}/external/benchmark/tmp
  STAMP_DIR           ${CMAKE_BINARY_DIR}/external/benchmark/stamp
  DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/benchmark/download
  SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/benchmark/src
  BINARY_DIR          ${CMAKE_BINARY_DIR}/external/benchmark/build
  )

find_package(Threads REQUIRED)
add_executable(matrix_bench ${CMAKE_CURRENT_SOURCE_DIR}/matrix_multiplication.cpp)
target_compile_features(matrix_bench
  PUBLIC cxx_std_17
  PRIVATE cxx_lambdas)
target_include_directories(matrix_bench
  PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/external/include>)
target_link_libraries(matrix_bench ${CMAKE_BINARY_DIR}/external/lib/libbenchmark.a ${CMAKE_THREAD_LIBS_INIT})
add_dependencies(matrix_bench google-benchmark)

add_executable(cache_bench ${CMAKE_CURRENT_SOURCE_DIR}/cache_locality.cpp)
target_compile_features(cache_bench
  PUBLIC cxx_std_17
  PRIVATE cxx_lambdas)
target_include_directories(cache_bench
  PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/external/include>)
target_link_libraries(cache_bench ${CMAKE_BINARY_DIR}/external/lib/libbenchmark.a ${CMAKE_THREAD_LIBS_INIT})
add_dependencies(cache_bench google-benchmark)
