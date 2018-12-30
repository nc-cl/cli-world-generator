#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;

uniform mat4 model, view, projection;

flat out vec4 fragcol;

void main () {
    gl_Position = projection * view * model * vec4(pos, 1.0);
    fragcol = vec4(col, 1.0);
}
