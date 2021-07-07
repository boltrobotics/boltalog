setup_dep(utility $ENV{UTILITY_HOME} SUB_DIR "") 
setup_dep(devices $ENV{DEVICES_HOME} SUB_DIR "")

include(logger)
setup_logger(${ROOT_SOURCE_DIR}/model/logger.mdl)

include(test_project)
find_test_srcs()

build_tests(
  SRCS ${SOURCES} ${LOG_SRCS}
  SUFFIX "-tests"
  INC_DIRS ${utility_INC_DIR} ${devices_INC_DIR} ${LOG_INC_DIR}
  DEPS ${PROJECT_NAME}-autogen ${PROJECT_NAME}-logging)

set(DOXYGEN_WARN NO)
build_doc(DEP ${PROJECT_NAME}-tests SUFFIX "-docs")
