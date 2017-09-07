set(GSL_ROOT ${CMAKE_BINARY_DIR}/gsl-download)
find_program(GSL gsl PATHS "${GSL_ROOT}/src/src")

if (NOT GSL)
    message("GSL not found")

    # Configure
    configure_file(CMakeListsGSL.txt "${GSL_ROOT}/CMakeLists.txt")

	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
		RESULT_VARIABLE result
        WORKING_DIRECTORY "${GSL_ROOT}")

	if (result)
        message(FATAL_ERROR "CMake step for GSL failed: ${result}")
	endif()

    # Download and unpack
	execute_process(COMMAND ${CMAKE_COMMAND} --build .
    	RESULT_VARIABLE result
        WORKING_DIRECTORY "${GSL_ROOT}")

    if (result)
        message(FATAL_ERROR "Build step for GSL failed: ${result}")
    endif()

    set(GSL "${GSL_ROOT}/src/src/gsl")
else()
    message("GSL found: ${GSL}")
endif()

file(GLOB SOURCES "*.cpp")
message("Using log model: ${LOG_MODEL}")

add_custom_command(
    OUTPUT ${INCLUDE_DIR}/logger.hpp
    COMMAND ${GSL} -script:${MODEL_DIR}/logger.hpp.mdl ${LOG_MODEL}
    WORKING_DIRECTORY ${INCLUDE_DIR}
    COMMENT "Generating logger.hpp from ${LOG_MODEL}" VERBATIM
    DEPENDS ${LOG_MODEL} ${MODEL_DIR}/logger.hpp.mdl
)
add_custom_command(
    OUTPUT ${SOURCE_DIR}/logger.cpp
    COMMAND ${GSL} -script:${MODEL_DIR}/logger.cpp.mdl ${LOG_MODEL}
    WORKING_DIRECTORY ${SOURCE_DIR}
    COMMENT "Generating logger.cpp from ${LOG_MODEL}" VERBATIM
    DEPENDS ${LOG_MODEL} ${MODEL_DIR}/logger.cpp.mdl
)
add_custom_command(
    OUTPUT ${SCRIPT_DIR}/log_viewer.py
    COMMAND ${GSL} -script:${MODEL_DIR}/log_viewer.py.mdl ${LOG_MODEL}
    WORKING_DIRECTORY ${SCRIPT_DIR}
    COMMENT "Generating log_viewer.py from ${LOG_MODEL}" VERBATIM
    DEPENDS ${LOG_MODEL} ${MODEL_DIR}/log_viewer.py.mdl
)
add_custom_target(
    log_viewer ALL
    DEPENDS ${SCRIPT_DIR}/log_viewer.py
)

list(APPEND SOURCES ${INCLUDE_DIR}/logger.hpp logger.cpp)
add_library(logger SHARED ${SOURCES})
