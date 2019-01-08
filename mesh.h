#include <GL/glew.h>
#include <vector>

class Mesh {
    protected:
        std::vector<GLfloat> _vertices;
        std::vector<unsigned int> _indices;
        GLuint _vao;
        GLuint _vbo;
        GLuint _ebo;
    public:
        virtual void draw() = 0;
};
