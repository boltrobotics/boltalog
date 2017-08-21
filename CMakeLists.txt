cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)
project("Logger")

if (NOT DEFINED LOG_MODEL)
    message(FATAL_ERROR "LOG_MODEL is not defined")
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LOGGER_VERSION_MAJOR 1)
set(LOGGER_VERSION_MINOR 0)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(MODEL_DIR ${CMAKE_SOURCE_DIR}/model)
set(SCRIPT_DIR ${CMAKE_SOURCE_DIR}/scripts)
set(LOG_MODEL ${CMAKE_SOURCE_DIR}/${LOG_MODEL})

include_directories(${INCLUDE_DIR})
add_subdirectory(${SOURCE_DIR})
enable_testing()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
        "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
endif()

if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings} -g -std=c++14" CACHE STRING "C++ flags" FORCE)
    set(CONFIGURED_ONCE TRUE CACHE INTERNAL "CMake is configured at least once")
endif()
