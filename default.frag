#version 330 core

flat in vec4 fragcol;
out vec4 finalcol;

void main () {
    finalcol = fragcol;
}
