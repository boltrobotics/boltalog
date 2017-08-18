set(GSL_ROOT ${CMAKE_BINARY_DIR}/gsl-download)
find_program(GSL gsl PATHS ${GSL_ROOT}/src/src)

if (NOT GSL)
    message("GSL not found")

    # Configure
    configure_file(CMakeListsGSL.txt ${GSL_ROOT}/CMakeLists.txt)

	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
		RESULT_VARIABLE result
        WORKING_DIRECTORY ${GSL_ROOT})

	if (result)
        message(FATAL_ERROR "CMake step for GSL failed: ${result}")
	endif()

    # Download and unpack
	execute_process(COMMAND ${CMAKE_COMMAND} --build .
    	RESULT_VARIABLE result
        WORKING_DIRECTORY ${GSL_ROOT})

    if (result)
        message(FATAL_ERROR "Build step for GSL failed: ${result}")
    endif()
else()
    message("GSL found: ${GSL}")
endif()

file(GLOB SOURCES "*.cpp")

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

list(APPEND SOURCES ${INCLUDE_DIR}/logger.hpp logger.cpp)
add_library(logger SHARED ${SOURCES})

add_subdirectory(test)
