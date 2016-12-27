#include "shader_program_builder.h"
#include <iostream>

ShaderProgramBuilder::ShaderProgramBuilder()
{
}

ShaderProgramBuilder::~ShaderProgramBuilder()
{
}

ShaderProgramBuilder & ShaderProgramBuilder::newProgram()
{
    //Clear everything
    clear();
    return *this;
}

ShaderProgramBuilder & ShaderProgramBuilder::addShader(std::shared_ptr<Shader> shader)
{
    shaders.push_back(shader);
    return *this;
}

std::shared_ptr<ShaderProgram> ShaderProgramBuilder::build()
{
    GLuint programRef = glCreateProgram();
    for(auto & elem : shaders){
        glAttachShader(programRef, elem.get()->getShaderRef());
    }
    glLinkProgram(programRef);
    std::unique_ptr<GLchar[]> logBuffer(new GLchar[ShaderProgramBuilder::logBufferSize]);
    GLsizei logLength;
    glGetProgramInfoLog(programRef, ShaderProgramBuilder::logBufferSize, &logLength, logBuffer.get());
    std::cout << logBuffer.get() << std::endl;

    return std::shared_ptr<ShaderProgram>(new ShaderProgram(programRef));
}

void ShaderProgramBuilder::clear()
{
    shaders.clear();
}
