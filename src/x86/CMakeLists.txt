set(BOARD_FAMILY x86)
set(CMAKE_MACOSX_RPATH 1)

include(project_setup)

####################################################################################################
# CTPP2 {

set(CTPP2_HOME $ENV{CTPP2_HOME})
add_subdirectory(${CTPP2_HOME} ${PROJECT_BINARY_DIR}/ctpp2)
include_directories(${CTPP2_HOME}/include)

# } CTPP2

####################################################################################################
# spdlog {

set(SPDLOG_HOME $ENV{SPDLOG_HOME})
add_subdirectory(${SPDLOG_HOME} ${PROJECT_BINARY_DIR}/spdlog)
include_directories(${SPDLOG_HOME}/include)

# } spdlog

####################################################################################################
# autogen {

set(TMPL_DIR "${PROJECT_SOURCE_DIR}/template")
set(PREFIX "${TMPL_DIR}/logger")
set(SCRIPT_PRE "${TMPL_DIR}/log_viewer")

add_custom_command(
  OUTPUT ${PREFIX}.hppct2
  COMMAND ctpp2c ${PREFIX}.hpptmpl ${PREFIX}.hppct2
  WORKING_DIRECTORY ${TMPL_DIR}
  COMMENT "Generating ${PREFIX}.hppct2 from ${PREFIX}.hpptmpl" VERBATIM
  DEPENDS ${PREFIX}.hpptmpl
  )

add_custom_command(
  OUTPUT ${PREFIX}.cppct2
  COMMAND ctpp2c ${PREFIX}.cpptmpl ${PREFIX}.cppct2
  WORKING_DIRECTORY ${TMPL_DIR}
  COMMENT "Generating ${PREFIX}.cppct2 from ${PREFIX}.cpptmpl" VERBATIM
  DEPENDS ${PREFIX}.cpptmpl
  )

add_custom_command(
  OUTPUT ${SCRIPT_PRE}.pyct2
  COMMAND ctpp2c ${SCRIPT_PRE}.pytmpl ${SCRIPT_PRE}.pyct2
  WORKING_DIRECTORY ${TMPL_DIR}
  COMMENT "Generating ${SCRIPT_PRE}.pyct2 from ${SCRIPT_PRE}.pytmpl" VERBATIM
  DEPENDS ${SCRIPT_PRE}.pytmpl
  )

add_custom_target(
  boltalog_templates
  DEPENDS ctpp2c ${PREFIX}.hppct2 ${PREFIX}.hpptmpl ${PREFIX}.cppct2 ${PREFIX}.cpptmpl 
    ${SCRIPT_PRE}.pyct2 ${SCRIPT_PRE}.pytmpl 
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
  target_link_libraries(${PROJECT_NAME}_autogen ${PROJECT_NAME} ctpp2)
  add_dependencies(${PROJECT_NAME}_autogen ctpp2c boltalog_templates)
endif ()

# } boltalog
