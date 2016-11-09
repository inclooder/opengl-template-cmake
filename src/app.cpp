#include "app.h"
#include "shader.h"
#include "vertex.h"
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLuint vaoID;
GLuint vboVerticesID;
GLuint vboIndicesID;

Vertex vertices[3];
GLushort indices[3];

glm::mat4 P = glm::mat4(1);
glm::mat4 MV = glm::mat4(1);

Shaders shaders;
ShaderProgram * shaderProgram;

App::App(){
}

App::~App(){
}

void App::init(){
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

void App::deinit(){
    if(shaderProgram){
        delete shaderProgram;
    }
}

void App::update(){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram->use();
    glUniformMatrix4fv(shaderProgram->operator()("MVP"), 1, GL_FALSE, glm::value_ptr(P*MV));
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
    shaderProgram->unuse();
}
void App::setViewport(unsigned int width, unsigned int height){
    glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
    P = glm::ortho(-1, 1, -1, 1);
}
