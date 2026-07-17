cmake_minimum_required(VERSION 3.14)
project(Verteilen2 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(ENABLE_CLI "CLI module" OFF)
option(ENABLE_CLIENT "Client module" OFF)
option(ENABLE_COMMON "Core module" OFF)
option(ENABLE_MASTER "Master module" OFF)
option(ENABLE_SERVER "Server module" OFF)

if(ENABLE_CLI or ENABLE_CLIENT or ENABLE_MASTER or ENABLE_SERVER)
    set(ENABLE_COMMON ON CACHE BOOL "" FORCE)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/bin)

find_package(Protobuf REQUIRED)

enable_testing()

option(MDNS_CPP_BUILD_EXAMPLE "Build example executables" OFF)

add_subdirectory("${CMAKE_SOURCE_DIR}/lib/crow")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/mdns")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/sqlite")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/spdlog")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/libhv")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/uuid")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/efsw")

add_subdirectory("${CMAKE_SOURCE_DIR}/src/native/cli")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/native/client")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/native/common")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/native/master")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/native/server")

add_subdirectory("${CMAKE_SOURCE_DIR}/tests/native")
