#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <map>
#include <GL/glew.h>

class Shader {
    public:
        Shader();
        ~Shader();

        void loadFromString(GLenum whichShader, const std::string & source);
        void loadFromFile(GLenum whichShader, const std::string & filePath);
        void createAndLinkProgram();
        void use();
        void unuse();
        void addAttribute(const std::string & attribute);
        void addUniform(const std::string & uniform);
        GLuint operator[](const std::string & attribute);
        GLuint operator()(const std::string & uniform);
        void deleteShaderProgram();
    private:
        enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER };
        GLuint program;
        int totalShaders;
        
        std::map<std::string, GLuint> attributeList;
        std::map<GLuint, GLuint> shadersByType;
        
        std::map<std::string, GLuint> uniformLocationList;


};



#endif /* end of include guard: SHADER_H */
