cmake_minimum_required(VERSION 3.19)

project(adventure-game LANGUAGES CXX C)

include(cmake/LibDeploy.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Only top-level library is compiled to .so, 
# which means we need to maintain PIC in static
# targets
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Python3 REQUIRED COMPONENTS Interpreter)

if(GENERATOR_IS_MULTI_CONFIG)
    message(FATAL_ERROR "multi-configuration builds are not supported")
endif()

add_subdirectory(godot-cpp)
add_subdirectory(src)
