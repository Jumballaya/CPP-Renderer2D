#version 460 core

out vec4 outColor;

in vec2 v_texCoord;
in vec4 v_color;
in float v_layer;

uniform sampler2D u_texture;

void main() {
    outColor = texture(u_texture, v_texCoord) * v_color;
}