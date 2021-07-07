include(x86_project)
include(ctpp2)

####################################################################################################
# boltalog-autogen {

if (NOT TARGET ${PROJECT_NAME}-autogen)
  build_exe(SRCS ${MAIN_SRC} LIBS ${ctpp2_LIB} SUFFIX "-autogen" INC_DIRS ${ctpp2_INC_DIR})
endif ()

# } boltalog-autogen 
