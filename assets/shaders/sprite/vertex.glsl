#version 460 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in mat4 a_transform;
layout(location = 5) in vec4 a_color;
layout(location = 6) in float a_layer;
layout(location = 7) in vec4 a_texRect;

out vec2 v_texCoord;


void main() {
    gl_Position = a_position;
    v_texCoord = a_uv;
    v_texCoord.y = 1.0 - v_texCoord.y;
}