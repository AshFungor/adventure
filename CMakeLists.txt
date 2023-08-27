cmake_minimum_required(VERSION 3.5)

project(example-lib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GODOT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/godot-cpp")
set(GODOT_BINARY_DIR "${GODOT_SOURCE_DIR}/build/bin")
set(GODOT_GEN_INCLUDE_DIR "${GODOT_SOURCE_DIR}/build/gen/include")
set(GODOT_INCLUDE_DIR "${GODOT_SOURCE_DIR}/include")
set(GODOT_GDINTERFACE_DIR "${GODOT_SOURCE_DIR}/gdextension")

file(GLOB godot-cpp
    "${GODOT_BINARY_DIR}/*godot-cpp*")

file(GLOB_RECURSE sources
    CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/*.cpp")

file(GLOB_RECURSE headers
    CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.h"
    "${CMAKE_SOURCE_DIR}/src/*.hpp")

add_library(example-lib SHARED
            ${sources}
            ${headers})

target_include_directories(example-lib PRIVATE
                           ${GODOT_INCLUDE_DIR}
                           ${GODOT_GEN_INCLUDE_DIR}
                           ${GODOT_GDINTERFACE_DIR})
target_link_libraries(example-lib ${godot-cpp})
