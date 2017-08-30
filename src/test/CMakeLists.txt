find_package(GTest)

if (GTEST_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
else()
    set(GTEST_ROOT "${CMAKE_BINARY_DIR}/gtest-download")

    # Download and unpack
    configure_file(CMakeListsGTest.txt "${GTEST_ROOT}/CMakeLists.txt")

    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY "${GTEST_ROOT}")

    if (result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY "${GTEST_ROOT}")

    if (result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    # Prevent overriding the parent project's compiler/linker settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines the gtest and gtest_main
    # targets.
    if (NOT TARGET gtest)
        add_subdirectory("${GTEST_ROOT}/src" "${GTEST_ROOT}/build")
    endif()
endif()

file(GLOB SOURCES "*.cpp")
add_executable(logger_test ${SOURCES})
target_link_libraries(logger_test logger gtest_main)
add_test(logger_test logger_test)
