include(x86_project)
setup_x86()

setup_dep(ctpp2 $ENV{CTPP2_HOME} SUB_DIR "./" LIB_NAME ctpp2)

####################################################################################################
# Templates {

set(BOLTALOG_TMPL_DIR "${ROOT_SOURCE_DIR}/template")
set(LOGGER_BASE "${BOLTALOG_TMPL_DIR}/logger")

add_custom_command(
  OUTPUT ${LOGGER_BASE}.hppct2
  COMMAND ctpp2c ${LOGGER_BASE}.hpptmpl ${LOGGER_BASE}.hppct2
  WORKING_DIRECTORY ${BOLTALOG_TMPL_DIR}
  COMMENT "Generating ${LOGGER_BASE}.hppct2 from ${LOGGER_BASE}.hpptmpl" VERBATIM
  DEPENDS ${LOGGER_BASE}.hpptmpl
  )

add_custom_command(
  OUTPUT ${LOGGER_BASE}.cppct2
  COMMAND ctpp2c ${LOGGER_BASE}.cpptmpl ${LOGGER_BASE}.cppct2
  WORKING_DIRECTORY ${BOLTALOG_TMPL_DIR}
  COMMENT "Generating ${LOGGER_BASE}.cppct2 from ${LOGGER_BASE}.cpptmpl" VERBATIM
  DEPENDS ${LOGGER_BASE}.cpptmpl
  )

set(LOG_VIEWER_BASE "${BOLTALOG_TMPL_DIR}/log-viewer")

add_custom_command(
  OUTPUT ${LOG_VIEWER_BASE}.pyct2
  COMMAND ctpp2c ${LOG_VIEWER_BASE}.pytmpl ${LOG_VIEWER_BASE}.pyct2
  WORKING_DIRECTORY ${BOLTALOG_TMPL_DIR}
  COMMENT "Generating ${LOG_VIEWER_BASE}.pyct2 from ${LOG_VIEWER_BASE}.pytmpl" VERBATIM
  DEPENDS ${LOG_VIEWER_BASE}.pytmpl
  )

if (NOT TARGET boltalog-templates)
  add_custom_target(
    boltalog-templates
    DEPENDS ctpp2c ${LOGGER_BASE}.hppct2 ${LOGGER_BASE}.cppct2 ${LOG_VIEWER_BASE}.pyct2
    )
endif ()

# } Templates

####################################################################################################
# boltalog-autogen {

if (NOT TARGET ${PROJECT_NAME}-autogen)
  build_exe(SRCS "${MAIN_SRC}" LIBS ${BTR_LIBS} SUFFIX "-autogen")
  add_dependencies(${PROJECT_NAME}-autogen boltalog-templates)
endif ()

# } boltalog-autogen 
