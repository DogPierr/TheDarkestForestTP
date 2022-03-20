cmake_minimum_required(VERSION 3.16.3)
project(TheDarkestForest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

set (CMAKE_CXX_STANDARD 17)

set(SOURCE_FILE "${PROJECT_SOURCE_DIR}/main.cpp")

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(GAME "${SOURCE_FILE}")

target_link_libraries(GAME sfml-graphics)