include(project_setup)

include(gtest)
list(APPEND LIBRARIES ${gtest_LIB_NAME})

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
set(AUTOGEN_DST "${PROJECT_SOURCE_DIR}/test")

add_custom_command(
  OUTPUT ${AUTOGEN_DST}/logger.hpp
  COMMAND ${TMPL_VM} ${TMPL_DIR}/logger.hpp.ct2 ${MODEL} logger.hpp 0 102400
  WORKING_DIRECTORY ${AUTOGEN_DST}
  COMMENT "Generating logger.hpp from ${MODEL}" VERBATIM
  DEPENDS templates ${MODEL} ${TMPL_VM} ${TMPL_DIR}/logger.hpp.ct2
  )

add_custom_command(
  OUTPUT ${AUTOGEN_DST}/logger.cpp
  COMMAND ${TMPL_VM} ${TMPL_DIR}/logger.cpp.ct2 ${MODEL} logger.cpp 0 102400
  WORKING_DIRECTORY ${AUTOGEN_DST}
  COMMENT "Generating logger.cpp from ${MODEL}" VERBATIM
  DEPENDS templates ${MODEL} ${TMPL_VM} ${TMPL_DIR}/logger.cpp.ct2
  )

include_directories(
  ${gtest_INC_DIR}
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/src/${BOARD_FAMILY}
)

file(GLOB SOURCES "*.cpp")
list(APPEND SOURCES ${AUTOGEN_DST}/logger.cpp ${AUTOGEN_DST}/logger.hpp)
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

# } boltalog
