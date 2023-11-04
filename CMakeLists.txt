cmake_minimum_required(VERSION 3.5)

project(extension-lib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GODOT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/godot-cpp")
set(GODOT_BINARY_DIR "${GODOT_SOURCE_DIR}/build/bin")
set(GODOT_GEN_INCLUDE_DIR "${GODOT_SOURCE_DIR}/build/gen/include")
set(GODOT_INCLUDE_DIR "${GODOT_SOURCE_DIR}/include")
set(GODOT_GDINTERFACE_DIR "${GODOT_SOURCE_DIR}/gdextension")

set(EXTENSION_LIB_SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(POSTBUILD_HOOK "postbuild-hook.sh")

add_compile_definitions(EXLIB_BUILD_DIR="${CMAKE_BINARY_DIR}")

find_package(plog REQUIRED)

file(GLOB godot-cpp
    "${GODOT_BINARY_DIR}/*godot-cpp*")

file(GLOB_RECURSE sources
    CONFIGURE_DEPENDS
    "${EXTENSION_LIB_SRC_DIR}/*.c"
    "${EXTENSION_LIB_SRC_DIR}/*.cpp")

file(GLOB_RECURSE headers
    CONFIGURE_DEPENDS
    "${EXTENSION_LIB_SRC_DIR}/*.h"
    "${EXTENSION_LIB_SRC_DIR}/*.hpp")

add_library(extension-lib SHARED
            ${sources}
            ${headers})

target_include_directories(extension-lib PRIVATE
                           ${EXTENSION_LIB_SRC_DIR}
                           ${GODOT_INCLUDE_DIR}
                           ${GODOT_GEN_INCLUDE_DIR}
                           ${GODOT_GDINTERFACE_DIR})

target_link_libraries(extension-lib PRIVATE ${godot-cpp})
target_link_libraries(extension-lib PRIVATE plog::plog)

file(COPY ${POSTBUILD_HOOK} DESTINATION ${CMAKE_BINARY_DIR})

add_custom_command(TARGET extension-lib
                   POST_BUILD
                   COMMAND ${CMAKE_BINARY_DIR}/${POSTBUILD_HOOK})
