#include "shader_program.h"
#include <iostream>

ShaderProgram::~ShaderProgram(){
    glDeleteProgram(this->programRef);
}


ShaderProgram::ShaderProgram(GLuint programRef)
{
    this->programRef = programRef;
}

void ShaderProgram::use(){
    glUseProgram(this->programRef);
}

void ShaderProgram::unuse(){
    glUseProgram(0);
}

GLuint ShaderProgram::attribute(const std::string & attribute){
    if(attributeList.find(attribute) == attributeList.end()){

        GLint currentProgramTmp;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgramTmp);
        GLuint currentProgram = static_cast<GLuint>(currentProgramTmp);
        if(currentProgram != this->programRef)
        {
            glUseProgram(this->programRef);
        }
        attributeList[attribute] = glGetAttribLocation(this->programRef, attribute.c_str());

        if(currentProgram != this->programRef)
        {
            glUseProgram(currentProgram);
        }
    }
    return attributeList[attribute];
}

GLuint ShaderProgram::uniform(const std::string & uniform){
    if(uniformLocationList.find(uniform) == uniformLocationList.end()){
        GLint currentProgramTmp;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgramTmp);
        GLuint currentProgram = static_cast<GLuint>(currentProgramTmp);
        if(currentProgram != this->programRef)
        {
            glUseProgram(this->programRef);
        }
        uniformLocationList[uniform] = glGetUniformLocation(this->programRef, uniform.c_str());

        if(currentProgram != this->programRef)
        {
            glUseProgram(currentProgram);
        }
    }
    return uniformLocationList[uniform];
}
