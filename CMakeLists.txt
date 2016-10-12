cmake_minimum_required(VERSION 2.8)
project(opengl-template)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Debug)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

# GLFW configuration
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(Threads REQUIRED)

include_directories(
    ${opengl-template_SOURCE_DIR}/inc 
    ${GLUT_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

set(SOURCES
    src/main.cpp
    src/shader.cpp
    src/shader_program.cpp
)

add_executable(opengl-template ${SOURCES})
target_link_libraries(
    opengl-template 
    glfw
    ${CMAKE_THREAD_LIBS_INIT}
    ${OPENGL_LIBRARIES} 
    ${GLUT_LIBRARIES} 
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY run.bash DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

