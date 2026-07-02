cmake_minimum_required(VERSION 3.14)
project(Verteilen2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/bin)

add_compile_definitions(BOOST_ERROR_CODE_HEADER_ONLY)
add_compile_definitions(BOOST_SYSTEM_NO_LIB)

find_package(Threads REQUIRED)

add_library(local_boost INTERFACE)
target_include_directories(local_boost INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boost/include
)

add_library(local_asio INTERFACE)
target_include_directories(local_asio INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/asio/include
)

add_library(local_beast INTERFACE)
target_include_directories(local_beast INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/beast/include
)

enable_testing()

option(MDNS_CPP_BUILD_EXAMPLE "Build example executables" OFF)

add_subdirectory("${CMAKE_SOURCE_DIR}/src/common")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/crow")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/mdns")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/sqlite")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/spdlog")

add_subdirectory("${CMAKE_SOURCE_DIR}/src/cli")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/client")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/master")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/server")

add_subdirectory("${CMAKE_SOURCE_DIR}/tests")