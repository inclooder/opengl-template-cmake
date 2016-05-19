#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <map>
#include "shader.h"


const int WIDTH = 1280;
const int HEIGHT = 960;

Shader shader;

void OnShutdown(){

}

void OnRender(){
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}


void OnResize(int newWidth, int newHeight){

}

void OnInit(){
  shader.loadFromFile(GL_VERTEX_SHADER, "data/shaders/simple.vert");
  shader.loadFromFile(GL_FRAGMENT_SHADER, "data/shaders/simple.frag");
}

std::map<std::string, int> attributeList;

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitContextVersion(3, 3);
    glutInitContextFlags(GLUT_CORE_PROFILE | GLUT_DEBUG);
    glutInitContextProfile(GLUT_FORWARD_COMPATIBLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Opengl Window");
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    if(GLEW_OK != glewError){
        std::cerr << "Error: " << glewGetErrorString(glewError) << std::endl;
    } 

    std::cout << "GL_VERSION = " << glGetString(GL_VERSION) << std::endl;

    OnInit();

    glutCloseFunc(OnShutdown);
    glutDisplayFunc(OnRender);
    glutReshapeFunc(OnResize);
    glutMainLoop();

    return 0;
}
