cmake_minimum_required(VERSION 3.16)
project(boltalog)

set(ROOT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(CMAKE_MODULE_PATH $ENV{CMAKEHELPERS_HOME}/cmake/Modules ${ROOT_SOURCE_DIR}/cmake/Modules)
include(main_project)
