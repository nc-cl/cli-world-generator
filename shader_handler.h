// Shader program handler class.
// Used to build a shader program and maintain its state.

#ifndef SHADER_HANDLER_H_
#define SHADER_HANDLER_H_

#include <GL/glew.h>

class ShaderHandler {
    private:
        GLuint _vertex_sh;
        GLuint _fragment_sh;
        GLuint _program;
    public:
        ShaderHandler(void);
        ~ShaderHandler(void);
        void compileShader(GLenum sh_type, std::string fpath);
        void linkShaders(void);
        GLuint getProgram(void);
};

#endif
