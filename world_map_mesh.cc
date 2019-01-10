#include "world_map_mesh.h"

WorldMapMesh::WorldMapMesh(const WorldMap *wmap) {
    // Vertex generation
    const unsigned int width = wmap->getWidth(), height = wmap->getHeight(),
        v_width = width + 1, v_height = height + 1,
        num_vertices = v_width * v_height;

    float vertex_step = 0.2f;

    float z_avg, z_avg_divisor;
    bool at_n_bound, at_e_bound, at_s_bound, at_w_bound;
    int prev_x, next_x, prev_y, next_y;

    for (int i = 0; i < num_vertices; i++) {
        // XY values
        _vertices.push_back((i % v_width) *  vertex_step);
        _vertices.push_back((i / v_width) * -vertex_step);

        // Z value
        z_avg = 0.0f;
        z_avg_divisor = 0.0f;

        at_n_bound = i / v_width == 0;
        at_e_bound = i % v_width == v_width  - 1;
        at_s_bound = i / v_width == v_height - 1;
        at_w_bound = i % v_width == 0;

        prev_x = i % v_width - 1;
        next_x = i % v_width;
        prev_y = i / v_width - 1;
        next_y = i / v_width;

        if (!at_n_bound && !at_w_bound) {
            z_avg += (*wmap)(prev_x, prev_y);
            z_avg_divisor += 1.0f;
        }
        if (!at_n_bound && !at_e_bound) {
            z_avg += (*wmap)(next_x, prev_y);
            z_avg_divisor += 1.0f;
        }
        if (!at_s_bound && !at_w_bound) {
            z_avg += (*wmap)(prev_x, next_y);
            z_avg_divisor += 1.0f;
        }
        if (!at_s_bound && !at_e_bound) {
            z_avg += (*wmap)(next_x, next_y);
            z_avg_divisor += 1.0f;
        }

        z_avg /= z_avg_divisor;
        _vertices.push_back(z_avg * 2.0f - 1.0f);
    }
    
    // Vertex indices
    const unsigned int num_indices = ((v_width * 2) * height) + height;

    GLuint restart_i = 0xFFFFFFFF;
    for (int i = 0; _indices.size() < num_indices; i++) {
        _indices.push_back(i);
        _indices.push_back(i + v_width);
        if ((i + 1) % v_width == 0) _indices.push_back(restart_i);
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

void WorldMapMesh::draw() {
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLE_STRIP, _indices.size(), GL_UNSIGNED_INT, 0);
    glFinish();
    glBindVertexArray(0);
}
