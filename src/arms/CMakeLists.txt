cmake_minimum_required(VERSION 3.5)

set(MODULE_NAME arms)

set(SOURCES arms.cpp)
set(HEADERS arms.hpp)

add_library(${MODULE_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${MODULE_NAME} PUBLIC ${SRC_DIR})
target_link_libraries(${MODULE_NAME} PUBLIC godot-cpp plog)