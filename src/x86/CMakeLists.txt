include(x86_project)
include(ctpp2)

####################################################################################################
# boltalog-autogen {

if (NOT TARGET ${PROJECT_NAME}-autogen)
  build_exe(
    SRCS ${MAIN_SRC}
    LIBS ${ctpp2_LIB_NAME}
    SUFFIX "-autogen"
    INC_DIRS ${ctpp2_INC_DIR}
    PIC ON)
endif ()

# } boltalog-autogen 
