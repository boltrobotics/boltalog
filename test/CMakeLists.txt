include(project_setup)

include(gtest)
list(APPEND LIBRARIES ${gtest_LIB_NAME})

####################################################################################################
# utility {

add_project(
  PREFIX utility
  HOME "$ENV{UTILITY_HOME}"
  URL "ssh://sergey@panda:2222/volume1/homes/sergey/dev/projects/utility.git")

include_directories(${utility_INC_DIR})

# }

####################################################################################################
# spdlog {

add_project(
  PREFIX spdlog
  HOME "$ENV{SPDLOG_HOME}"
  URL "https://github.com/gabime/spdlog")

include_directories(${spdlog_INC_DIR})

# } spdlog

####################################################################################################
# boltalog {

set(TMPL_VM "${PROJECT_NAME}_autogen")
set(TMPL_DIR "${PROJECT_SOURCE_DIR}/template")
set(MODEL "${TMPL_DIR}/model_example.mdl")
set(SRC_DST "${PROJECT_SOURCE_DIR}/test")
set(SCRIPT_DST "${PROJECT_SOURCE_DIR}/script")

add_custom_command(
  OUTPUT ${SRC_DST}/logger.hpp
  COMMAND ${TMPL_VM} ${TMPL_DIR}/logger.hppct2 ${MODEL} logger.hpp 0 102400
  WORKING_DIRECTORY ${SRC_DST}
  COMMENT "Generating logger.hpp from ${MODEL}" VERBATIM
  DEPENDS ${TMPL_VM} ${TMPL_DIR}/logger.hppct2 ${MODEL}
  )

add_custom_command(
  OUTPUT ${SRC_DST}/logger.cpp
  COMMAND ${TMPL_VM} ${TMPL_DIR}/logger.cppct2 ${MODEL} logger.cpp 0 102400
  WORKING_DIRECTORY ${SRC_DST}
  COMMENT "Generating logger.cpp from ${MODEL}" VERBATIM
  DEPENDS ${TMPL_VM} ${TMPL_DIR}/logger.cppct2 ${MODEL}
  )

add_custom_command(
  OUTPUT ${SCRIPT_DST}/log_viewer.py
  COMMAND ${TMPL_VM} ${TMPL_DIR}/log_viewer.pyct2 ${MODEL} log_viewer.py 0 102400
  WORKING_DIRECTORY ${SCRIPT_DST}
  COMMENT "Generating log_viewer.py from ${MODEL}" VERBATIM
  DEPENDS ${TMPL_VM} ${TMPL_DIR}/log_viewer.pyct2 ${MODEL}
  )

add_custom_target(
  log_viewer
  DEPENDS ${SCRIPT_DST}/log_viewer.py
  )
include_directories(
  ${gtest_INC_DIR}
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/src/${BOARD_FAMILY}
)

file(GLOB SOURCES "*.cpp")
list(APPEND SOURCES ${SRC_DST}/logger.cpp ${SRC_DST}/logger.hpp)
list(APPEND LIBRARIES ${gtest_LIB_NAME} ${PROJECT_NAME})

add_definitions(-D${BOARD_FAMILY})
add_compile_options(-Wall -Wextra -Werror)

add_executable(${PROJECT_NAME}_tests ${SOURCES})

set_property(
  TARGET ${PROJECT_NAME}_tests
  PROPERTY INSTALL_RPATH
  "@loader_path/../lib"
)

target_link_libraries(${PROJECT_NAME}_tests ${LIBRARIES})
add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)
add_dependencies(${PROJECT_NAME}_tests log_viewer)

# } boltalog
