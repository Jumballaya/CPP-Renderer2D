#version 460 core

out vec4 outColor;

in vec2 v_texCoord;

void main() {
    outColor = vec4(v_texCoord, 1.0, 1.0);
}