#include "shader.h"
#include <iostream>
#include <fstream>
#include <GL/freeglut.h>

Shader::Shader() : totalShaders(0){
    
}

Shader::~Shader(){
}

void Shader::loadFromString(GLenum shaderType, const std::string & source){
    GLuint shaderRef = glCreateShader(shaderType);
    shadersByType.insert(std::pair<GLuint, GLuint>(shaderType, shaderRef));

    const char * sourceCode = source.c_str();
    glShaderSource(shaderRef, 1, &sourceCode, 0);
    glCompileShader(shaderRef);

    GLchar logBuffer[2048];
    GLsizei logLength;
    glGetShaderInfoLog(shaderRef, sizeof(logBuffer), &logLength, logBuffer);

    /*
     * We need to add one because length
     * returned from glGetShaderInfoLog 
     * doesn't include null terminator character.
     */
    GLsizei nullTerminatorPosition = logLength + 1; 
    logBuffer[nullTerminatorPosition] = 0; 

    std::cout << logBuffer << std::endl;
}

void Shader::loadFromFile(GLenum whichShader, const std::string & filePath){
    std::string shaderCode;
    std::ifstream inputFile(filePath);
    inputFile.seekg(0, std::ios::end);
    shaderCode.reserve(inputFile.tellg());
    inputFile.seekg(0, std::ios::beg);

    shaderCode.assign((std::istreambuf_iterator<char>(inputFile)),
                       std::istreambuf_iterator<char>());

    this->loadFromString(whichShader, shaderCode);
}

void Shader::createAndLinkProgram(){
    this->program = glCreateProgram();
    for(auto & elem : this->shadersByType){
        glAttachShader(this->program, elem.second);
    }
    glLinkProgram(this->program);

    GLchar logBuffer[2048];
    GLsizei logLength;
    glGetProgramInfoLog(this->program, sizeof(logBuffer), &logLength, logBuffer);
    /*
     * We need to add one because length
     * returned from glGetShaderInfoLog 
     * doesn't include null terminator character.
     */
    GLsizei nullTerminatorPosition = logLength + 1; 
    logBuffer[nullTerminatorPosition] = 0; 
    std::cout << logBuffer << std::endl;
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
