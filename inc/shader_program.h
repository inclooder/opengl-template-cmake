#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "shader.h"

typedef std::vector<std::shared_ptr<Shader>> Shaders;

class ShaderProgram {
    public:
        ~ShaderProgram();
        ShaderProgram(GLuint programRef);
        void use();
        void unuse();
        GLuint attribute(const std::string & attribute);
        GLuint uniform(const std::string & uniform);
    private:
        GLuint programRef;
        std::map<std::string, GLuint> attributeList;
        std::map<std::string, GLuint> uniformLocationList;
};

#endif /* end of include guard: SHADER_PROGRAM_H */
