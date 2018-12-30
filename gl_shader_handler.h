#include <GL/glew.h>

#ifndef GL_SHADER_HANDLER_H_
#define GL_SHADER_HANDLER_H_

class GlShaderHandler {
    private:
        GLuint _vertex_sh;
        GLuint _fragment_sh;
        GLuint _program;
    public:
        GlShaderHandler(void);
        ~GlShaderHandler(void);
        void compileShader(GLenum sh_type, std::string fpath);
        void linkShaders(void);
        GLuint getProgram(void);
};

#endif
