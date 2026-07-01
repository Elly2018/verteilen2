cmake_minimum_required(VERSION 3.14)
project(Verteilen2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

enable_testing()

add_subdirectory("${CMAKE_SOURCE_DIR}/src/common")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/crow")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/mdns")

add_subdirectory("${CMAKE_SOURCE_DIR}/src/cli")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/client")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/master")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/server")

add_subdirectory("${CMAKE_SOURCE_DIR}/tests")