include(init)

setup_dep(utility $ENV{UTILITY_HOME} SUB_DIR "") 
setup_dep(devices $ENV{DEVICES_HOME} SUB_DIR "")

include(logger)
setup_logger(${ROOT_SOURCE_DIR}/model/boltalog_logger.mdl SRC_DIR ${CMAKE_BINARY_DIR}/test)

include(x86_project)
find_test_srcs()

# When building in Release mode, get sporadic errors (inconsistent, from different code):
# "...relocation truncated to fit: R_X86_64_PC32 against `.bss'..."
# Changed to custom-compiled gtest, the errors are gone
add_compile_options("-mcmodel=large")

build_exe(
  SRCS ${SOURCES} ${AUTOGEN_LOG_SRCS}
  SUFFIX "-tests"
  INC_DIRS ${utility_INC_DIR} ${devices_INC_DIR} ${AUTOGEN_LOG_INC_DIR}
  DEPS ${PROJECT_NAME}-autogen ${PROJECT_NAME}-logging
  PIC OFF
  TEST ON)

#target_compile_options(boltalog-tests PRIVATE "-mcmodel=large")
#target_link_options(boltalog-tests PRIVATE "LINKER:--no-relax")

set(DOXYGEN_WARN NO)
build_doc(DEP ${PROJECT_NAME}-tests SUFFIX "-docs")
