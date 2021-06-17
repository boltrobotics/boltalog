include(x86_project)
include(ctpp2)

####################################################################################################
# Templates {

set(BOLTALOG_TMPL_DIR "${ROOT_SOURCE_DIR}/template")
set(LOGGER_BASE "${BOLTALOG_TMPL_DIR}/logger")

add_custom_command(
  OUTPUT ${LOGGER_BASE}.hppct2
  COMMAND ${ctpp2_C} ${LOGGER_BASE}.hpptmpl ${LOGGER_BASE}.hppct2
  WORKING_DIRECTORY ${BOLTALOG_TMPL_DIR}
  COMMENT "Generating ${LOGGER_BASE}.hppct2 from ${LOGGER_BASE}.hpptmpl" VERBATIM
  DEPENDS ${LOGGER_BASE}.hpptmpl
  )

add_custom_command(
  OUTPUT ${LOGGER_BASE}.cppct2
  COMMAND ${ctpp2_C} ${LOGGER_BASE}.cpptmpl ${LOGGER_BASE}.cppct2
  WORKING_DIRECTORY ${BOLTALOG_TMPL_DIR}
  COMMENT "Generating ${LOGGER_BASE}.cppct2 from ${LOGGER_BASE}.cpptmpl" VERBATIM
  DEPENDS ${LOGGER_BASE}.cpptmpl
  )

set(VIEWER_BASE "${BOLTALOG_TMPL_DIR}/log-viewer")

add_custom_command(
  OUTPUT ${VIEWER_BASE}.pyct2
  COMMAND ${ctpp2_C} ${VIEWER_BASE}.pytmpl ${VIEWER_BASE}.pyct2
  WORKING_DIRECTORY ${BOLTALOG_TMPL_DIR}
  COMMENT "Generating ${VIEWER_BASE}.pyct2 from ${VIEWER_BASE}.pytmpl" VERBATIM
  DEPENDS ${VIEWER_BASE}.pytmpl
  )

if (NOT TARGET boltalog-templates)
  add_custom_target(
    boltalog-templates
    DEPENDS ctpp2_project ${LOGGER_BASE}.hppct2 ${LOGGER_BASE}.cppct2 ${VIEWER_BASE}.pyct2
    )
endif ()

# } Templates

####################################################################################################
# boltalog-autogen {

if (NOT TARGET ${PROJECT_NAME}-autogen)
  build_exe(INC_DIRS ${ctpp2_INC_DIR} SRCS "${MAIN_SRC}" LIBS ${ctpp2_LIB} SUFFIX "-autogen")
  add_dependencies(${PROJECT_NAME}-autogen boltalog-templates)
endif ()

# } boltalog-autogen 
