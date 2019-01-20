#version 330 core

layout (location = 0) in vec3 pos;

uniform float sea_level;
uniform mat4 model, view, projection;

smooth out vec4 fragcol;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0);

    float normal_z = (pos.z + 1.0) / 2.0;

    if (normal_z >= sea_level) {
        fragcol = vec4(0.0, 0.8, 0.0, 1.0f);
    } else {
        fragcol = vec4(0.0, 0.4, 1.0, 1.0f);
    }
}
