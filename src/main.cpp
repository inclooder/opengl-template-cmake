#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <map>
#include "shader.h"
#include "vertex.h"
#include <iomanip>
#include <cstddef>


#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


const int WIDTH = 1280;
const int HEIGHT = 960;

GLuint vaoID;
GLuint vboVerticesID;
GLuint vboIndicesID;

Vertex vertices[3];
GLushort indices[3];

glm::mat4 P = glm::mat4(1);
glm::mat4 MV = glm::mat4(1);

Shaders shaders;
ShaderProgram * shaderProgram;

void OnShutdown(){
    if(shaderProgram){
        delete shaderProgram;
    }

}

void OnRender(){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram->use();
    glUniformMatrix4fv(shaderProgram->operator()("MVP"), 1, GL_FALSE, glm::value_ptr(P*MV));
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
    shaderProgram->unuse();

    glutSwapBuffers();
}


void OnResize(int newWidth, int newHeight){
    glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);
    P = glm::ortho(-1, 1, -1, 1);
}

void OnInit(){
    std::shared_ptr<Shader> defaultVertShader = Shader::loadFromFile(GL_VERTEX_SHADER, "data/shaders/simple.vert");
    std::shared_ptr<Shader> defaultFragShader = Shader::loadFromFile(GL_FRAGMENT_SHADER, "data/shaders/simple.frag");
    shaders.push_back(defaultVertShader);
    shaders.push_back(defaultFragShader);

    shaderProgram = new ShaderProgram(shaders);
    shaderProgram->use();
    shaderProgram->addAttribute("vVertex");
    shaderProgram->addAttribute("vColor");
    shaderProgram->addAttribute("MVP");
    shaderProgram->unuse();

    vertices[0].color = glm::vec3(1, 0, 0);
    vertices[1].color = glm::vec3(0, 1, 0);
    vertices[2].color = glm::vec3(0, 0, 1);

    vertices[0].position = glm::vec3(-1, -1, 0);
    vertices[1].position = glm::vec3(0, 1, 0);
    vertices[2].position = glm::vec3(1, -1, 0);

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;


    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboVerticesID); //This could be changed into one call. To consider later..
    glGenBuffers(1, &vboIndicesID);
    GLsizei stride = sizeof(Vertex);

    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);


    glEnableVertexAttribArray(shaderProgram->operator[]("vVertex"));
    glVertexAttribPointer(shaderProgram->operator[]("vVertex"), 3, GL_FLOAT, GL_FALSE, stride, 0);


    glEnableVertexAttribArray(shaderProgram->operator[]("vColor"));
    glVertexAttribPointer(
            shaderProgram->operator[]("vColor"),
            3, 
            GL_FLOAT,
            GL_FALSE,
            stride,
            reinterpret_cast<const GLvoid *>(offsetof(Vertex, color))
    ); 


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

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
