cmake_minimum_required(VERSION 3.19)

set(SOURCES player.cpp arms.cpp)
set(HEADERS player.hpp arms.hpp)

add_library(player STATIC ${SOURCES} ${HEADERS})

target_link_libraries(player PUBLIC godot-cpp common)

target_include_directories(player PUBLIC ${CMAKE_SOURCE_DIR})
