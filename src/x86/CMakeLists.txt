set(BOARD_FAMILY x86)
set(CMAKE_MACOSX_RPATH 1)

include(project_setup)

####################################################################################################
# CTPP2 {

set(CTPP2_HOME $ENV{CTPP2_HOME})
include_directories(${CTPP2_HOME}/include)

if (NOT TARGET ctpp2)
  add_subdirectory(${CTPP2_HOME} ${PROJECT_BINARY_DIR}/ctpp2)
endif ()

# } CTPP2

####################################################################################################
# spdlog {

set(SPDLOG_HOME $ENV{SPDLOG_HOME})
include_directories(${SPDLOG_HOME}/include)

if (NOT TARGET spdlog)
  add_subdirectory(${SPDLOG_HOME} ${PROJECT_BINARY_DIR}/spdlog)
endif ()

# } spdlog

####################################################################################################
# autogen {

set(TMPL_DIR "${PROJECT_SOURCE_DIR}/template")
set(LOGGER "${TMPL_DIR}/logger")

add_custom_command(
  OUTPUT ${LOGGER}.hppct2
  COMMAND ctpp2c ${LOGGER}.hpptmpl ${LOGGER}.hppct2
  WORKING_DIRECTORY ${TMPL_DIR}
  COMMENT "Generating ${LOGGER}.hppct2 from ${LOGGER}.hpptmpl" VERBATIM
  DEPENDS ${LOGGER}.hpptmpl
  )

add_custom_command(
  OUTPUT ${LOGGER}.cppct2
  COMMAND ctpp2c ${LOGGER}.cpptmpl ${LOGGER}.cppct2
  WORKING_DIRECTORY ${TMPL_DIR}
  COMMENT "Generating ${LOGGER}.cppct2 from ${LOGGER}.cpptmpl" VERBATIM
  DEPENDS ${LOGGER}.cpptmpl
  )

set(LOG_VIEWER "${TMPL_DIR}/log_viewer")

add_custom_command(
  OUTPUT ${LOG_VIEWER}.pyct2
  COMMAND ctpp2c ${LOG_VIEWER}.pytmpl ${LOG_VIEWER}.pyct2
  WORKING_DIRECTORY ${TMPL_DIR}
  COMMENT "Generating ${LOG_VIEWER}.pyct2 from ${LOG_VIEWER}.pytmpl" VERBATIM
  DEPENDS ${LOG_VIEWER}.pytmpl
  )

add_custom_target(
  boltalog_templates
  DEPENDS
    ctpp2c
    ${LOGGER}.hppct2 ${LOGGER}.hpptmpl ${LOGGER}.cppct2 ${LOGGER}.cpptmpl 
    ${LOG_VIEWER}.pyct2 ${LOG_VIEWER}.pytmpl 
  )

# } autogen

####################################################################################################
# boltalog {

find_package(Threads)

include_directories(
  ${PROJECT_SOURCE_DIR}/src/${BOARD_FAMILY}
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/include
)

set(MAIN_SRC ${PROJECT_SOURCE_DIR}/src/${BOARD_FAMILY}/main.cpp)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/${BOARD_FAMILY}/*.c*")
list(REMOVE_ITEM SOURCES ${MAIN_SRC})

add_definitions(-D${BOARD_FAMILY})
add_compile_options(-Wall -Wextra -Werror)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

add_executable(${PROJECT_NAME}_autogen ${MAIN_SRC})
add_dependencies(${PROJECT_NAME}_autogen boltalog_templates)
target_link_libraries(${PROJECT_NAME}_autogen ${PROJECT_NAME} ctpp2)

# } boltalog
