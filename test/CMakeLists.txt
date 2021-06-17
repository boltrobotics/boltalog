setup_dep(utility $ENV{UTILITY_HOME} SUB_DIR "") 
setup_dep(devices $ENV{DEVICES_HOME} SUB_DIR "")
setup_dep(spdlog $ENV{SPDLOG_HOME} SUB_DIR "")

####################################################################################################
# boltalog test {

include(logger)
add_logger(INC_DIR ${PROJECT_SOURCE_DIR}/test SRC_DIR ${PROJECT_SOURCE_DIR}/test)

include(test_project)
find_test_srcs()

build_tests(
  SRCS ${SOURCES} ${BOLTALOG_SOURCES}
  SUFFIX "-tests"
  INC_DIRS ${utility_INC_DIR} ${devices_INC_DIR}
  DEPS ${PROJECT_NAME}-autogen ${PROJECT_NAME}-logging)

set(DOXYGEN_WARN NO)
build_doc(DEP ${PROJECT_NAME}-tests SUFFIX "-docs")

# } boltalog test
