cmake_minimum_required(VERSION 2.8)
project(opengl-template)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
include_directories(
    ${opengl-template_SOURCE_DIR}/inc 
    ${GLUT_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
)

add_subdirectory(test)

add_executable(opengl-template src/main.cpp)
target_link_libraries(
    opengl-template 
    ${OPENGL_LIBRARIES} 
    ${GLUT_LIBRARIES} 
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)

