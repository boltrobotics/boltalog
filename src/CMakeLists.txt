file(GLOB SOURCES "*.cpp")

add_custom_command(
    OUTPUT ${INCLUDE_DIR}/logger.hpp
    COMMAND gsl -script:${MODEL_DIR}/logger.hpp.mdl ${LOG_MODEL}
    WORKING_DIRECTORY ${INCLUDE_DIR}
    COMMENT "Generating logger.hpp from ${LOG_MODEL}" VERBATIM
    DEPENDS ${LOG_MODEL} ${MODEL_DIR}/logger.hpp.mdl
)
add_custom_command(
    OUTPUT ${SOURCE_DIR}/logger.cpp
    COMMAND gsl -script:${MODEL_DIR}/logger.cpp.mdl ${LOG_MODEL}
    WORKING_DIRECTORY ${SOURCE_DIR}
    COMMENT "Generating logger.cpp from ${LOG_MODEL}" VERBATIM
    DEPENDS ${LOG_MODEL} ${MODEL_DIR}/logger.cpp.mdl
)

list(APPEND SOURCES ${INCLUDE_DIR}/logger.hpp logger.cpp)

add_library(logger SHARED ${SOURCES})

add_subdirectory(test)
