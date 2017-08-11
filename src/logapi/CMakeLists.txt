include_directories("${SOURCE_DIR}/logapiimpl")

file(GLOB SOURCES "*.cpp")
add_executable(logapi ${SOURCES})
target_link_libraries(logapi logapiimpl)
