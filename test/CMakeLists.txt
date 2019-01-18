include(gtest)

####################################################################################################
# utility {

set(UTILITY_HOME $ENV{UTILITY_HOME})
include_directories(${UTILITY_HOME}/include)

if (NOT TARGET utility)
  add_subdirectory(${UTILITY_HOME} ${PROJECT_BINARY_DIR}/utility)
endif ()

# }

####################################################################################################
# spdlog {

set(SPDLOG_HOME $ENV{SPDLOG_HOME})
include_directories(${SPDLOG_HOME}/include)

if (NOT TARGET spdlog)
  add_subdirectory(${SPDLOG_HOME} ${PROJECT_BINARY_DIR}/spdlog)
endif ()

# } spdlog

####################################################################################################
# boltalog {

set(TMPL_VM "${PROJECT_NAME}_autogen")
set(TMPL_DIR "${PROJECT_SOURCE_DIR}/template")
set(MODEL "${PROJECT_SOURCE_DIR}/model/example.mdl")
set(SRC_DST "${PROJECT_SOURCE_DIR}/test")

add_custom_command(
  OUTPUT ${SRC_DST}/logger.hpp
  COMMAND ${TMPL_VM} ${TMPL_DIR}/logger.hppct2 ${MODEL} ${SRC_DST}/logger.hpp 0 102400
  WORKING_DIRECTORY ${SRC_DST}
  COMMENT "Generating ${SRC_DST}/logger.hpp from ${MODEL}" VERBATIM
  DEPENDS ${TMPL_VM} ${TMPL_DIR}/logger.hppct2 ${MODEL}
  )

add_custom_command(
  OUTPUT ${SRC_DST}/logger.cpp
  COMMAND ${TMPL_VM} ${TMPL_DIR}/logger.cppct2 ${MODEL} ${SRC_DST}/logger.cpp 0 102400
  WORKING_DIRECTORY ${SRC_DST}
  COMMENT "Generating ${SRC_DST}/logger.cpp from ${MODEL}" VERBATIM
  DEPENDS ${TMPL_VM} ${TMPL_DIR}/logger.cppct2 ${MODEL}
  )

add_custom_command(
  OUTPUT ${SRC_DST}/log_viewer.py
  COMMAND ${TMPL_VM} ${TMPL_DIR}/log_viewer.pyct2 ${MODEL} ${SRC_DST}/log_viewer.py 0 102400
  WORKING_DIRECTORY ${SRC_DST}
  COMMENT "Generating ${SRC_DST}/log_viewer.py from ${MODEL}" VERBATIM
  DEPENDS ${TMPL_VM} ${TMPL_DIR}/log_viewer.pyct2 ${MODEL}
  )

add_custom_target(
  log_viewer
  DEPENDS ${SRC_DST}/log_viewer.py
  )

include_directories(
  ${gtest_inc_dir}
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/src/${BOARD_FAMILY}
)

file(GLOB SOURCES "*.cpp")
list(APPEND SOURCES ${SRC_DST}/logger.cpp ${SRC_DST}/logger.hpp)

add_definitions(-D${BOARD_FAMILY})
add_compile_options(-Wall -Wextra -Werror)

add_executable(${PROJECT_NAME}_tests ${SOURCES})
set_property(TARGET ${PROJECT_NAME}_tests PROPERTY install_rpath "@loader_path/../lib")
target_link_LIBRARIES(${PROJECT_NAME}_tests ${gtest_LIB_NAME} ${PROJECT_NAME})

add_test(NAME ${PROJECT_NAME}_tests COMMAND $<TARGET_FILE:${PROJECT_NAME}_tests>)
add_dependencies(${PROJECT_NAME}_tests log_viewer)

# } boltalog
