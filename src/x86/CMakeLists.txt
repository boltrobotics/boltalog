set(BOARD_FAMILY x86)
include(project_setup)

set(CMAKE_MACOSX_RPATH 1)

####################################################################################################
# CTPP2 {

find_program(CTPP2C ctpp2c PATHS "${EXECUTABLE_OUTPUT_PATH}")
if (NOT CTPP2C)
  list(APPEND FORCE_UPDATE_ctpp2c FORCE_UPDATE)
  list(APPEND FORCE_UPDATE_ctpp2c 1)
  set(CTPP2C ${EXECUTABLE_OUTPUT_PATH}/ctpp2c)
endif ()

add_project(
  PREFIX ctpp2
  HOME "$ENV{CTPP2_HOME}"
  URL "ssh://sergey@panda:2222/volume1/homes/sergey/dev/projects/_third_party/ctpp.git"
  ${FORCE_UPDATE_ctpp2c})

include_directories(${ctpp2_INC_DIR})

# } CTPP2

####################################################################################################
# spdlog {

add_project(
  PREFIX spdlog
  HOME "$ENV{SPDLOG_HOME}"
  URL "https://github.com/gabime/spdlog")

include_directories(${spdlog_INC_DIR})

# } spdlog

####################################################################################################
# autogen {

set(TMPL_DIR "${PROJECT_SOURCE_DIR}/template")
set(PREFIX "${TMPL_DIR}/logger")

add_custom_command(
  OUTPUT ${PREFIX}.hpp.ct2
  COMMAND ${CTPP2C} ${PREFIX}.hpp.tmpl ${PREFIX}.hpp.ct2
  WORKING_DIRECTORY ${TMPL_DIR}
  COMMENT "Generating ${PREFIX}.hpp.ct2 from ${PREFIX}.hpp.tmpl" VERBATIM
  DEPENDS ${PREFIX}.hpp.tmpl ctpp2c
  )

add_custom_command(
  OUTPUT ${PREFIX}.cpp.ct2
  COMMAND ${CTPP2C} ${PREFIX}.cpp.tmpl ${PREFIX}.cpp.ct2
  WORKING_DIRECTORY ${TMPL_DIR}
  COMMENT "Generating ${PREFIX}.cpp.ct2 from ${PREFIX}.cpp.tmpl" VERBATIM
  DEPENDS ${PREFIX}.cpp.tmpl ctpp2c
  )

add_custom_target(
  templates ALL
  DEPENDS ${PREFIX}.cpp.ct2 ${PREFIX}.cpp.tmpl ${PREFIX}.hpp.ct2 ${PREFIX}.hpp.tmpl
    ${PROJECT_NAME}_autogen ctpp2c
  )

# } autogen

####################################################################################################
# boltalog {

include_directories(
  ${PROJECT_SOURCE_DIR}/src/${BOARD_FAMILY}
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/include
)

set(MAIN_CPP ${PROJECT_SOURCE_DIR}/src/${BOARD_FAMILY}/main.cpp)
file(GLOB SOURCES "*.c*" "${PROJECT_SOURCE_DIR}/src/*.c*")
list(REMOVE_ITEM SOURCES ${MAIN_CPP})
list(LENGTH SOURCES SOURCES_LEN)

if (SOURCES_LEN GREATER 0)
  add_definitions(-D${BOARD_FAMILY})
  add_compile_options(-Wall -Wextra -Werror)

  find_package(Threads)

  add_library(${PROJECT_NAME} SHARED ${SOURCES})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES})

  add_executable(${PROJECT_NAME}_autogen ${MAIN_CPP})
  target_link_libraries(${PROJECT_NAME}_autogen ${PROJECT_NAME} ${ctpp2_LIB_NAME})
endif ()

# } boltalog
