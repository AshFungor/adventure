# TODO: support the whole configuration for gdextension config
function(deploy_binary_target)
    set(ARGS "TARGET;DESTINATION;BASE_DIR;ENTRY_SYMBOL;MIN_COMPAT")
    cmake_parse_arguments(args "" "${ARGS}" "" ${ARGN})

    if(args_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "deploy_binary_target called with invalid arguments: ${args_UNPARSED_ARGUMENTS}")
    endif()

    foreach(required_arg IN ITEMS TARGET DESTINATION BASE_DIR ENTRY_SYMBOL MIN_COMPAT)
        if(NOT args_${required_arg})
            message(FATAL_ERROR "deploy_binary_target: ${required_arg} argument is required")
        endif()
    endforeach()

    set(TARGET_ARCH "${CMAKE_SYSTEM_PROCESSOR}")
    set(TARGET_SYSTEM "${CMAKE_SYSTEM_NAME}")
    set(TARGET_BUILD_TYPE "${CMAKE_BUILD_TYPE}")

    string(TOLOWER "${TARGET_SYSTEM}.${TARGET_BUILD_TYPE}.${TARGET_ARCH}" MANIFEST_KEY)

    set(BINARY_SUFFIX "$<TARGET_FILE_SUFFIX:${args_TARGET}>")
    set(BINARY_STEM "$<TARGET_FILE_BASE_NAME:${args_TARGET}>")
    set(BINARY_PATH "${args_DESTINATION}/${BINARY_STEM}.${MANIFEST_KEY}${BINARY_SUFFIX}")
    set(MANIFEST_FILE "${args_DESTINATION}/manifest.json")
    
    add_custom_command(TARGET ${args_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:${args_TARGET}>
            # embed features into final binary name to distinguish it from others
            ${BINARY_PATH}
    )

    add_custom_command(TARGET ${args_TARGET} POST_BUILD
        COMMAND ${Python3_EXECUTABLE}
            "${CMAKE_SOURCE_DIR}/scripts/manifest.py"
            "${MANIFEST_KEY}" "${BINARY_PATH}" "${MANIFEST_FILE}"
    )

    add_custom_command(TARGET ${args_TARGET} POST_BUILD
        COMMAND ${Python3_EXECUTABLE}
            "${CMAKE_SOURCE_DIR}/scripts/gdextension.py"
            --manifest "${MANIFEST_FILE}"
            --base-dir "${args_BASE_DIR}"
            --output "${args_DESTINATION}/$<TARGET_NAME:${args_TARGET}>.gdextension"
            --entry-symbol "${args_ENTRY_SYMBOL}"
            --compat-min "${args_MIN_COMPAT}"
    )
endfunction()
