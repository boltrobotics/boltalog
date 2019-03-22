set(CMAKE_MACOSX_RPATH 1)

####################################################################################################
# CTPP2 {

set(CTPP2_HOME $ENV{CTPP2_HOME})
include_directories(${CTPP2_HOME}/include)

if (NOT TARGET ctpp2)
  add_subdirectory(${CTPP2_HOME} ${PROJECT_BINARY_DIR}/ctpp2)
endif ()

# } CTPP2

####################################################################################################
# autogen {

set(TMPL_DIR "${PROJECT_SOURCE_DIR}/template")
set(LOGGER "${TMPL_DIR}/logger")

add_custom_command(
  OUTPUT ${LOGGER}.hppct2
  COMMAND ctpp2c ${LOGGER}.hpptmpl ${LOGGER}.hppct2
  WORKING_DIRECTORY ${TMPL_DIR}
  COMMENT "Generating logger.hppct2 from logger.hpptmpl" VERBATIM
  DEPENDS ${LOGGER}.hpptmpl
  )

add_custom_command(
  OUTPUT ${LOGGER}.cppct2
  COMMAND ctpp2c ${LOGGER}.cpptmpl ${LOGGER}.cppct2
  WORKING_DIRECTORY ${TMPL_DIR}
  COMMENT "Generating logger.cppct2 from logger.cpptmpl" VERBATIM
  DEPENDS ${LOGGER}.cpptmpl
  )

set(LOG_VIEWER "${TMPL_DIR}/log-viewer")

add_custom_command(
  OUTPUT ${LOG_VIEWER}.pyct2
  COMMAND ctpp2c ${LOG_VIEWER}.pytmpl ${LOG_VIEWER}.pyct2
  WORKING_DIRECTORY ${TMPL_DIR}
  COMMENT "Generating log-viewer.pyct2 from log-viewer.pytmpl" VERBATIM
  DEPENDS ${LOG_VIEWER}.pytmpl
  )

add_custom_target(
  boltalog-templates
  DEPENDS
    ctpp2c
    ${LOGGER}.hppct2 ${LOGGER}.hpptmpl ${LOGGER}.cppct2 ${LOGGER}.cpptmpl 
    ${LOG_VIEWER}.pyct2 ${LOG_VIEWER}.pytmpl 
  )

# } autogen

####################################################################################################
# boltalog {

include(x86_project)

setup_x86()
build_exe(SRCS "${MAIN_SRC}" LIBS ctpp2 SUFFIX "-autogen")
add_dependencies(${PROJECT_NAME}-autogen boltalog-templates)

# } boltalog
