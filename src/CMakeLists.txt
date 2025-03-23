cmake_minimum_required(VERSION 3.19)

set(SOURCES register_types.cpp)
set(HEADERS register_types.hpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})

add_subdirectory(common)
add_subdirectory(player)

target_link_libraries(${PROJECT_NAME} PUBLIC player)

deploy_binary_target(
    TARGET "${PROJECT_NAME}"
    DESTINATION "${CMAKE_SOURCE_DIR}/game/bin"
)