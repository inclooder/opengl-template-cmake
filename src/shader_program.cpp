#include "shader.h"
#include <iostream>

ShaderProgram::~ShaderProgram(){
    glDeleteProgram(this->programRef);
}

ShaderProgram::ShaderProgram(const Shaders & shaders){
    this->programRef = glCreateProgram();
    for(auto & elem : shaders){
        glAttachShader(this->programRef, elem.get()->getShaderRef());
    }
    glLinkProgram(this->programRef);
    //std::shared_ptr<GLchar> logBuffer(new GLchar[ShaderProgram::logBufferSize], std::default_delete<GLchar[]>());
    std::unique_ptr<GLchar[]> logBuffer(new GLchar[ShaderProgram::logBufferSize]);
    GLsizei logLength;
    glGetProgramInfoLog(this->programRef, ShaderProgram::logBufferSize, &logLength, logBuffer.get());
    std::cout << logBuffer.get() << std::endl;
}

void ShaderProgram::use(){
    glUseProgram(this->programRef);
}

void ShaderProgram::unuse(){
    glUseProgram(0);
}

void ShaderProgram::addAttribute(const std::string & attribute){
    attributeList[attribute] = glGetAttribLocation(this->programRef, attribute.c_str());

}

void ShaderProgram::addUniform(const std::string & uniform){
    uniformLocationList[uniform] = glGetUniformLocation(this->programRef, uniform.c_str());
}


GLuint ShaderProgram::operator[](const std::string & attribute){
    return attributeList[attribute];
}

GLuint ShaderProgram::operator()(const std::string & uniform){
    return uniformLocationList[uniform];
}
