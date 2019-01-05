#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 model, view, projection;

smooth out vec4 fragcol;

void main () {
    gl_Position = projection * view * model * vec4(pos, 1.0);

    float normal_z = (pos.z + 1.0) / 2.0;
    fragcol = vec4(
        0.1,
        normal_z,
        max(0.1, 0.75 - normal_z),
        1.0
    );
}
