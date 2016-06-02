#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <map>
#include <GL/glew.h>
#include <vector>
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

typedef std::vector<std::shared_ptr<Shader>> Shaders;

class ShaderProgram {
    public:
        ~ShaderProgram();
        ShaderProgram(const Shaders & shaders);
        void use();
        void unuse();
        void addAttribute(const std::string & attribute);
        void addUniform(const std::string & uniform);
        GLuint operator[](const std::string & attribute);
        GLuint operator()(const std::string & uniform);
    private:
        Shaders shaders;
        GLuint programRef;
        std::map<std::string, GLuint> attributeList;
        std::map<std::string, GLuint> uniformLocationList;
        static constexpr const int logBufferSize = 2048;
};

#endif /* end of include guard: SHADER_H */
