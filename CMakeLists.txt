cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project("Log API")

# Project variables.
set(LOGAPI_VERSION_MAJOR 1)
set(LOGAPI_VERSION_MINOR 0)

# CMake variables.
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
enable_testing()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
endif()

# Compilation flags
if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings} -std=c++14"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

# Build instructions

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory("${SOURCE_DIR}/logapiimpl")
add_subdirectory("${SOURCE_DIR}/logapi")

add_test(logapi_test bin/logapi)

set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")
