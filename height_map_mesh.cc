#include "height_map_mesh.h"

HeightMapMesh::HeightMapMesh(const HeightMap *hmap) {
    // Vertex generation
    const unsigned int v_size_x = hmap->getSizeX() + 1,
        v_size_y = hmap->getSizeY() + 1,
        num_vertices = v_size_x * v_size_y;

    float vertex_step = 0.2f;

    float z_avg, z_avg_divisor;
    bool at_n_bound, at_e_bound, at_s_bound, at_w_bound;
    int prev_x, next_x, prev_y, next_y;

    for (unsigned int i = 0; i < num_vertices; i++) {
        // XY values
        _vertices.push_back((i % v_size_x) *  vertex_step);
        _vertices.push_back((i / v_size_x) * -vertex_step);

        // Z value
        z_avg = 0.0f;
        z_avg_divisor = 0.0f;

        at_n_bound = i / v_size_x == 0;
        at_e_bound = i % v_size_x == v_size_x  - 1;
        at_s_bound = i / v_size_x == v_size_y - 1;
        at_w_bound = i % v_size_x == 0;

        prev_x = i % v_size_x - 1;
        next_x = i % v_size_x;
        prev_y = i / v_size_x - 1;
        next_y = i / v_size_x;

        if (!at_n_bound && !at_w_bound) {
            z_avg += (*hmap)(prev_x, prev_y);
            z_avg_divisor += 1.0f;
        }
        if (!at_n_bound && !at_e_bound) {
            z_avg += (*hmap)(next_x, prev_y);
            z_avg_divisor += 1.0f;
        }
        if (!at_s_bound && !at_w_bound) {
            z_avg += (*hmap)(prev_x, next_y);
            z_avg_divisor += 1.0f;
        }
        if (!at_s_bound && !at_e_bound) {
            z_avg += (*hmap)(next_x, next_y);
            z_avg_divisor += 1.0f;
        }

        z_avg /= z_avg_divisor;
        _vertices.push_back(z_avg * 2.0f - 1.0f);
    }
    
    // Vertex indices
    const unsigned int num_indices = (v_size_x * 2 + 1) * (v_size_y - 1);

    GLuint restart_i = 0xFFFFFFFF;
    for (int i = 0; _indices.size() < num_indices; i++) {
        _indices.push_back(i);
        _indices.push_back(i + v_size_x);
        if ((i + 1) % v_size_x == 0) _indices.push_back(restart_i);
    }
    glPrimitiveRestartIndex(restart_i);

    // Buffer vertex + index data
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(GLfloat), &_vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), &_indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, nullptr);

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void HeightMapMesh::draw() {
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLE_STRIP, _indices.size(), GL_UNSIGNED_INT, 0);
    glFinish();
    glBindVertexArray(0);
}
