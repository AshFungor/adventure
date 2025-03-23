cmake_minimum_required(VERSION 3.19)

set(SOURCES initializer.cpp)
set(HEADERS initializer.hpp)

add_library(common STATIC ${SOURCES} ${HEADERS})

target_link_libraries(common PUBLIC godot-cpp)
target_include_directories(common PUBLIC ${CMAKE_SOURCE_DIR})