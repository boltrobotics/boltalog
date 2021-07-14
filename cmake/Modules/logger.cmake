include(ctpp2_model)

function (setup_logger model_path)
  cmake_parse_arguments(p "" "SRC_DIR" "" ${ARGN})

  set(VM "boltalog-autogen")
  set(TMPL_DIR "$ENV{BOLTALOG_HOME}/template")
  set(TMPL_NAME "logger")
  set(CT2_DIR "${CMAKE_CURRENT_BINARY_DIR}")

  if (NOT p_SRC_DIR)
    set(p_SRC_DIR ${CMAKE_BINARY_DIR}/src/common)
  endif ()

  if (model_path)
    get_filename_component(MODEL_ABS_PATH ${model_path} REALPATH BASE_DIR ${CMAKE_SOURCE_DIR})

    if (NOT EXISTS ${MODEL_ABS_PATH})
      message(FATAL_ERROR "File doesn't exist: ${model_path}")
    else ()
      set(model_path ${MODEL_ABS_PATH})
    endif ()

    get_filename_component(MODEL_NAME ${model_path} NAME_WE)

    # Generate logger.hpp and logger.cpp
    build_model(${model_path} ${VM} ${TMPL_NAME} ${p_SRC_DIR})

    # Generate log viewer python script
    #
    set(VIEWER_NAME "${MODEL_NAME}-viewer")
    set(TMPL_PATH ${TMPL_DIR}/log-viewer.pytmpl)
    set(CT2_PATH ${CT2_DIR}/${VIEWER_NAME}.pyct2)
    set(SCT_DIR ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/scripts)
    set(SCT_PATH ${SCT_DIR}/${VIEWER_NAME}.py)

    if (NOT EXISTS ${SCT_DIR}})
      file(MAKE_DIRECTORY ${SCT_DIR})
    endif ()

    add_custom_command(
      OUTPUT ${CT2_PATH}
      COMMAND ${ctpp2_C} ${TMPL_PATH} ${CT2_PATH}
      WORKING_DIRECTORY ${CT2_DIR}
      COMMENT "Generating ${CT2_PATH} from ${TMPL_PATH}" VERBATIM
      DEPENDS ${TMPL_PATH}
      )

    add_custom_command(
      OUTPUT ${SCT_PATH}
      COMMAND ${VM} ${CT2_PATH} ${model_path} ${SCT_PATH} 0 102400
      COMMAND chmod 755 ${SCT_PATH}
      WORKING_DIRECTORY ${SCT_DIR}
      COMMENT "Generating ${SCT_PATH} from ${model_path}" VERBATIM
      DEPENDS ${VM} ${CT2_PATH} ${model_path} 
      )

    # For boltalog tests, the target is boltalog-logging; for boltabus, it is boltabus-logging
    #
    add_custom_target(
      ${PROJECT_NAME}-logging
      DEPENDS ${PROJECT_NAME}-${MODEL_NAME}-model ${CT2_PATH} ${SCT_PATH}
      )

  endif (model_path)

  set(AUTOGEN_LOG_SRCS ${p_SRC_DIR}/${MODEL_NAME}.cpp PARENT_SCOPE)
  set(AUTOGEN_LOG_INC_DIR ${p_SRC_DIR} PARENT_SCOPE)

endfunction (setup_logger)
