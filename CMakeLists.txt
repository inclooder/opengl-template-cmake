cmake_minimum_required(VERSION 2.8)
project(opengl-template)

include_directories(${opengl-template_SOURCE_DIR}/inc)
add_subdirectory(test)

add_executable(opengl-template src/main.cpp)

