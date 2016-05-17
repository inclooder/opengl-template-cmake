#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

using namespace std;

const int WIDTH = 1280;
const int HEIGHT = 960;

void OnRender(){
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

void OnShutdown(){

}

void OnResize(int newWidth, int newHeight){

}

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
        cerr << "Error: " << glewGetErrorString(glewError) << endl;
    } 

    glutCloseFunc(OnShutdown);
    glutDisplayFunc(OnRender);
    glutReshapeFunc(OnResize);
    glutMainLoop();

    return 0;
}
