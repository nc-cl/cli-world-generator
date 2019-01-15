#include <fstream>
#include <streambuf>
#include <sstream>
#include <iostream>
#include "shader_handler.h"

const std::string SHADER_DIR = "shader/";

ShaderHandler::ShaderHandler() {}

ShaderHandler::~ShaderHandler() {
    glDetachShader(_program, _vertex_sh);
    glDetachShader(_program, _fragment_sh);
    glDeleteShader(_vertex_sh);
    glDeleteShader(_fragment_sh);
    glDeleteProgram(_program);
}

void ShaderHandler::compileShader(GLenum sh_type, std::string fpath) {
    std::ifstream infile(SHADER_DIR + fpath);
    std::string src_str = std::string(std::istreambuf_iterator<char>(infile),
        std::istreambuf_iterator<char>());
    const char* src = src_str.c_str();
    infile.close();

    GLuint shader = glCreateShader(sh_type);

    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, NULL, info_log);

        std::stringstream ss;
        ss << "vertex shader compilation failed\n\nshader src:\n" << src
            << "\nlog:\n" << info_log << std::endl;
        throw ss.str();
    }

    switch (sh_type) {
        case GL_VERTEX_SHADER:
            _vertex_sh = shader;
            break;
        case GL_FRAGMENT_SHADER:
            _fragment_sh = shader;
    }
}

void ShaderHandler::linkShaders() {
    _program = glCreateProgram();
    glAttachShader(_program, _vertex_sh);
    glAttachShader(_program, _fragment_sh);
    glLinkProgram(_program);

    int success;
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(_program, 512, NULL, info_log);

        std::stringstream ss;
        ss << "shader linking failed\n\nlog:\n" << info_log << std::endl;
        throw ss.str();
    }
}

GLuint ShaderHandler::getProgram() {
    return _program;
}
