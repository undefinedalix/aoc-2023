cmake_minimum_required(VERSION 3.5)

project(cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(01 day_01.cpp)
add_custom_target(resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources/
    ${CMAKE_CURRENT_BINARY_DIR}/resources/
)
add_dependencies(01 resources)
