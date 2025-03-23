function(deploy_binary_target)
    set(ARGS "TARGET;DESTINATION")
    cmake_parse_arguments(args "" "${ARGS}" "" ${ARGN})

    if(args_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "deploy_binary_target called with invalid arguments: ${args_UNPARSED_ARGUMENTS}")
    endif()

    if(NOT args_TARGET)
        message(FATAL_ERROR "deploy_binary_target: TARGET argument is required.")
    endif()

    if(NOT args_DESTINATION)
        message(FATAL_ERROR "deploy_binary_target: DESTINATION argument is required.")
    endif()

    # Add a post-build command to copy the binary to the destination
    add_custom_command(TARGET ${args_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:${args_TARGET}>
            ${args_DESTINATION}/$<TARGET_FILE_NAME:${args_TARGET}>
        COMMENT "Deploying ${args_TARGET} to ${args_DESTINATION}"
    )
endfunction()
