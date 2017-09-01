cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)
project("Logger")

if (NOT DEFINED LOG_MODEL)
    message(FATAL_ERROR "LOG_MODEL is not defined")
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(MODEL_DIR ${PROJECT_SOURCE_DIR}/model)
set(SCRIPT_DIR ${PROJECT_SOURCE_DIR}/scripts)

set(LOGGER_VERSION_MAJOR 1)
set(LOGGER_VERSION_MINOR 0)

enable_testing()

include_directories(${INCLUDE_DIR})
add_subdirectory(${SOURCE_DIR})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
        "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")

    if (NOT CONFIGURED_ONCE)
        set(CMAKE_CXX_FLAGS "${warnings} -g -std=c++14" CACHE STRING "C++ flags" FORCE)
        set(CONFIGURED_ONCE TRUE CACHE INTERNAL "CMake is configured at least once")
    endif()
endif()

