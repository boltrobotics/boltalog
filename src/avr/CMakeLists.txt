cmake_minimum_required(VERSION 3.5)
project(boltalog)

set(CMAKE_MODULE_PATH $ENV{CMAKEHELPERS_HOME}/cmake/Modules)
include(init)

####################################################################################################
# Firmware {

include_directories(
  ${BOLTALOG_SOURCE_DIR}/src/${BOARD_FAMILY}
  ${BOLTALOG_SOURCE_DIR}/src/common
  ${BOLTALOG_SOURCE_DIR}/include
)

file(GLOB_RECURSE SOURCES
  "${BOLTALOG_SOURCE_DIR}/src/${BOARD_FAMILY}/*.c"
  "${BOLTALOG_SOURCE_DIR}/src/${BOARD_FAMILY}/*.cpp"
  "${BOLTALOG_SOURCE_DIR}/src/common/*.c"
  "${BOLTALOG_SOURCE_DIR}/src/common/*.cpp")

#print_board_list()

add_definitions(-D${BOARD_FAMILY})
add_compile_options(-Wall -Wextra)

generate_arduino_library(
	${PROJECT_NAME}
  BOARD ${BOARD}
  BOARD_CPU ${BOARD_CPU}
  SRCS ${SOURCES}
)
