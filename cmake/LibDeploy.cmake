# deploys compiled GDExtension library to 
# game directory

function(deploy_binary_target)
    set(OPTIONS UPDATE)
    set(ARGS NAME DESTINATION)
    set(LIST_ARGS )
    
    cmake_parse_arguments(
        PARSE_ARGV 0
        BINARY_TARGET
        "${OPTIONS}"
        "${ARGS}"
        "${LIST_ARGS}"
    )

    foreach(ARG IN ITEMS ${BINARY_TARGET_UNPARSED_ARGUMENTS})
        message(WARNING "Argument is not parsed: ${ARG}")
    endforeach()

    # get binary target name
    get_target_property(BINARY_TARGET_NAME BINARY_TARGET_NAME $<LIBRARY_OUTPUT_NAME>)

    add_custom_command(TARGET ${BINARY_TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${BINARY_TARGET_NAME}> ${DEFINITION}/${BINARY_TARGET_NAME}
    )

endfunction()
