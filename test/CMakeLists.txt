include(x86_project)
find_test_srcs()

setup_dep(utility $ENV{UTILITY_HOME} SUB_DIR "") 

include(logger)
set(LOGGER_MODEL_NAME boltalog_logger)
setup_logger(${ROOT_SOURCE_DIR}/model/${LOGGER_MODEL_NAME}.mdl SRC_DIR ${CMAKE_BINARY_DIR}/test)

# When building in Release mode, get sporadic errors (inconsistent, from different code):
# "...relocation truncated to fit: R_X86_64_PC32 against `.bss'..."
# Changed to custom-compiled gtest, the errors are gone
add_compile_options("-mcmodel=large")

if (NOT DEFINED ENV{SPDLOG_HOME})
  message(FATAL_ERROR "*** SPDLOG_HOME undefined")
endif ()

if (NOT TARGET ${PROJECT_NAME}-tests)
  build_exe(
    SUFFIX "-tests"
    SRCS ${SOURCES} ${AUTOGEN_LOG_SRCS}
    INC_DIRS ${utility_INC_DIR} ${AUTOGEN_LOG_INC_DIR} "$ENV{SPDLOG_HOME}/include"
    DEPS ${PROJECT_NAME}-autogen ${LOGGER_MODEL_NAME}-logging
    PIC OFF
    TEST ON)
endif ()

set(DOXYGEN_WARN NO)
build_doc(DEP ${PROJECT_NAME}-tests SUFFIX "-docs")
