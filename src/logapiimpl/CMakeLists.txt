#function(generate target)
#    add_custom_command(
#        TARGET ${target}
#        PRE_BUILD
#        COMMAND ${target}
#        COMMAND ${target}
#        COMMAND ${target}
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#        COMMENT "Running ${target}" VERBATIM
#    )
#endfunction()

file(GLOB SOURCES "*.cpp")
add_library(logapiimpl SHARED ${SOURCES})
