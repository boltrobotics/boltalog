cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH $ENV{CMAKEHELPERS_HOME}/cmake/Modules)

if (NOT BUILD_LIB AND NOT BUILD_EXE)
  set(BUILD_LIB ON)
  set(BUILD_EXE OFF)
endif ()

include(avr_project)
