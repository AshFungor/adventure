cmake_minimum_required(VERSION 3.19)

set(SOURCES nodes.cpp)
set(HEADERS nodes.hpp)

add_library(common STATIC ${SOURCES} ${HEADERS})

target_link_libraries(common PUBLIC godot-cpp)
target_include_directories(common PUBLIC ${CMAKE_SOURCE_DIR})