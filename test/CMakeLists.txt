setup_dep(spdlog $ENV{SPDLOG_HOME} SUB_DIR "")
setup_dep(utility $ENV{UTILITY_HOME} SUB_DIR "") 

####################################################################################################
# boltalog test {

set(TMPL_VM "${PROJECT_NAME}-autogen")
set(TMPL_DIR "${PROJECT_SOURCE_DIR}/template")
set(MODEL "${PROJECT_SOURCE_DIR}/model/example.mdl")
set(SRC_DST "${PROJECT_SOURCE_DIR}/test")

add_custom_command(
  OUTPUT ${SRC_DST}/logger.hpp
  COMMAND ${TMPL_VM} ${TMPL_DIR}/logger.hppct2 ${MODEL} ${SRC_DST}/logger.hpp 0 102400
  WORKING_DIRECTORY ${SRC_DST}
  COMMENT "Generating logger.hpp from example.mdl" VERBATIM
  DEPENDS ${TMPL_VM} ${TMPL_DIR}/logger.hppct2 ${MODEL}
  )

add_custom_command(
  OUTPUT ${SRC_DST}/logger.cpp
  COMMAND ${TMPL_VM} ${TMPL_DIR}/logger.cppct2 ${MODEL} ${SRC_DST}/logger.cpp 0 102400
  WORKING_DIRECTORY ${SRC_DST}
  COMMENT "Generating logger.cpp from example.mdl" VERBATIM
  DEPENDS ${TMPL_VM} ${TMPL_DIR}/logger.cppct2 ${MODEL}
  )

add_custom_command(
  OUTPUT ${SRC_DST}/log-viewer.py
  COMMAND ${TMPL_VM} ${TMPL_DIR}/log-viewer.pyct2 ${MODEL} ${SRC_DST}/log-viewer.py 0 102400
  WORKING_DIRECTORY ${SRC_DST}
  COMMENT "Generating log-viewer.py from example.mdl" VERBATIM
  DEPENDS ${TMPL_VM} ${TMPL_DIR}/log-viewer.pyct2 ${MODEL}
  )

add_custom_target(
  log-viewer
  DEPENDS ${SRC_DST}/log-viewer.py
  )

include(test_project)
setup_tests()
find_test_srcs()
list(APPEND SOURCES ${SRC_DST}/logger.cpp ${SRC_DST}/logger.hpp)
build_tests(SRCS ${SOURCES} SUFFIX "-tests")
add_dependencies(${PROJECT_NAME}-tests log-viewer)

set(DOXYGEN_WARN NO)
build_doc(DEP ${PROJECT_NAME}-tests SUFFIX "-docs")

# } boltalog test
