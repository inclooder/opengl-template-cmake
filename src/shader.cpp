#include "shader.h"


Shader::Shader() : totalShaders(0){
    
}

Shader::~Shader(){
}

void Shader::loadFromString(GLenum shaderType, const std::string & source){
    GLuint shaderRef = glCreateShader(shaderType);
    shadersByType.insert(std::pair<GLuint, GLuint>(shaderType, shaderRef));

    glShaderSource(shaderRef, 1, source.c_str(), 0);
    glCompileShader(shaderRef);


}

void Shader::loadFromFile(GLenum whichShader, const std::string & filePath){
}

void Shader::createAndLinkProgram(){
}

void Shader::use(){
}

void Shader::unuse(){
}

void Shader::addAttribute(const std::string & attribute){
}

void Shader::addUniform(const std::string & uniform){
}

GLuint Shader::operator[](const std::string & attribute){
}

GLuint Shader::operator()(const std::string & uniform){
}

void Shader::deleteShaderProgram(){
}
