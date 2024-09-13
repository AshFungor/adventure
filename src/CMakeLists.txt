cmake_minimum_required(VERSION 3.5)

set(SOURCES register_types.cpp base.cpp)
set(HEADERS register_types.hpp base.hpp)

set(MODULES weapons player arms)

add_subdirectory(arms)
add_subdirectory(player)
add_subdirectory(weapons)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${SRC_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${MODULES})
