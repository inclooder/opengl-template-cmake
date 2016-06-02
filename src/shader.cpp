#include "shader.h"
#include <iostream>
#include <fstream>
#include <GL/freeglut.h>

Shader::Shader(GLenum shaderType, const std::string & source){
    this->shaderType = shaderType;
    this->shaderRef = glCreateShader(shaderType);
    //shadersByType.insert(std::pair<GLuint, GLuint>(shaderType, this->shaderRef));

    const char * sourceCode = source.c_str();
    glShaderSource(this->shaderRef, 1, &sourceCode, 0);
    glCompileShader(this->shaderRef);

    GLchar logBuffer[2048];
    GLsizei logLength;
    glGetShaderInfoLog(this->shaderRef, sizeof(logBuffer), &logLength, logBuffer);

    std::cout << logBuffer << std::endl;
}

Shader::~Shader(){
    glDeleteShader(this->shaderRef);
}

GLuint Shader::getShaderRef(){
    return this->shaderRef;
}

GLuint Shader::getShaderType(){
    return this->shaderType;
}

std::shared_ptr<Shader> Shader::loadFromString(GLenum whichShader, const std::string & source){
    std::shared_ptr<Shader> newShader(new Shader(whichShader, source));
    return newShader;
}

std::shared_ptr<Shader> Shader::loadFromFile(GLenum whichShader, const std::string & filePath){
    std::string shaderCode;
    std::ifstream inputFile(filePath);
    inputFile.seekg(0, std::ios::end);
    shaderCode.reserve(inputFile.tellg());
    inputFile.seekg(0, std::ios::beg);

    shaderCode.assign((std::istreambuf_iterator<char>(inputFile)),
                       std::istreambuf_iterator<char>());

    std::shared_ptr<Shader> newShader(new Shader(whichShader, shaderCode));
    return newShader;
}


