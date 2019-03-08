// Abstract mesh data class.
// Enforces presence of draw function, and eliminates the need to declare
// necessary data structures.

#ifndef MESH_H_
#define MESH_H_

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
        virtual void draw(void) = 0;
};

#endif
