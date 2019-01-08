#include <GL/glew.h>

#ifndef SHADER_HANDLER_H_
#define SHADER_HANDLER_H_

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
