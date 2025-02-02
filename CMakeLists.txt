cmake_minimum_required(VERSION 3.19)

project(adventure-game LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED VERSION 3.11.3)
find_package(GTest REQUIRED VERSION 1.14.0)
find_package(plog REQUIRED VERSION 1.1.10)
find_package(Boost REQUIRED VERSION 1.84.0)

add_subdirectory(godot-cpp)
add_subdirectory(src)
