include(x86_project)
include(ctpp2)

####################################################################################################
# boltalog-autogen {

if (NOT TARGET ${PROJECT_NAME}-autogen)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)

  build_exe(
    SRCS ${MAIN_SRC}
    LIBS ${ctpp2_LIB}
    SUFFIX "-autogen"
    INC_DIRS ${ctpp2_INC_DIR}
    DEPS ctpp2_LIB_DEP)
endif ()

# } boltalog-autogen 
