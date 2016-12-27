#ifndef SHADER_PROGRAM_BUILDER_H
#define SHADER_PROGRAM_BUILDER_H

#include <memory>
#include <GL/glew.h>
#include "shader.h"
#include "shader_program.h"

class ShaderProgramBuilder {
    public:
        ShaderProgramBuilder();
        ~ShaderProgramBuilder();
        ShaderProgramBuilder & newProgram();
        ShaderProgramBuilder & addShader(std::shared_ptr<Shader> shader);
        std::shared_ptr<ShaderProgram> build();
    private:
        void clear();
        std::vector<std::shared_ptr<Shader>> shaders;
        static constexpr const int logBufferSize = 2048;
};



#endif /* end of include guard: SHADER_PROGRAM_BUILDER_H */
