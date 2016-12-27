#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include <memory>

class Shader {
    public:
        Shader(GLenum shaderType, const std::string & source); 
        enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER };
        ~Shader();
        GLuint getShaderRef();
        GLenum getShaderType();

        static std::shared_ptr<Shader> loadFromString(GLenum whichShader, const std::string & source);
        static std::shared_ptr<Shader> loadFromFile(GLenum whichShader, const std::string & filePath);
    private:
        GLuint shaderRef;
        GLenum shaderType;
};

#endif /* end of include guard: SHADER_H */
