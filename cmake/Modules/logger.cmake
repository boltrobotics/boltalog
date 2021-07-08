include(ctpp2_model)

function (setup_logger model_path)
  cmake_parse_arguments(p "" "SRC_DIR;VM;TMPL_NAME;VIEWER_NAME" "" ${ARGN})

  set(VM "boltalog-autogen")
  set(TMPL_DIR "${ROOT_SOURCE_DIR}/template")
  set(CT2_DIR "${CMAKE_CURRENT_BINARY_DIR}")

  if (NOT p_SRC_DIR)
    set(p_SRC_DIR ${CMAKE_BINARY_DIR}/src/common)
  endif ()

  if (NOT p_TMPL_NAME)
    set(p_TMPL_NAME "logger")
  endif ()

  if (NOT p_VIEWER_NAME)
    set(p_VIEWER_NAME "log-viewer")
  endif ()

  if (model_path)
    get_filename_component(MODEL_ABS_PATH ${model_path} REALPATH BASE_DIR ${CMAKE_SOURCE_DIR})

    if (NOT EXISTS ${MODEL_ABS_PATH})
      message(FATAL_ERROR "File doesn't exist: ${model_path}")
    else ()
      set(model_path ${MODEL_ABS_PATH})
    endif ()

    # Generate logger.hpp and logger.cpp. Exports TMPL_DIR, CT2_DIR
    build_model(${model_path} ${VM} ${p_TMPL_NAME} ${p_SRC_DIR})

    # Generate log-viewer.py
    #
    set(TMPL_PATH ${TMPL_DIR}/${p_VIEWER_NAME}.pytmpl)
    set(CT2_PATH ${CT2_DIR}/${p_VIEWER_NAME}.pyct2)
    set(SCT_DIR ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/scripts)
    set(SCT_PATH ${SCT_DIR}/${p_VIEWER_NAME}.py)

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
    add_custom_target(${PROJECT_NAME}-logging
      DEPENDS ${p_TMPL_NAME}-tmpl ${CT2_PATH} ${SCT_PATH}
      )

  endif (model_path)

  set(LOG_SRCS ${p_SRC_DIR}/${p_TMPL_NAME}.cpp PARENT_SCOPE)
  set(LOG_INC_DIR ${p_SRC_DIR} PARENT_SCOPE)

endfunction (setup_logger)
