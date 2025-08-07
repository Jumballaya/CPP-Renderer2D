#version 460 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in mat4 a_transform;
layout(location = 6) in vec4 a_color;
layout(location = 7) in vec4 a_texRect;
layout(location = 8) in float a_layer;

out vec2 v_texCoord;
out vec4 v_color;
out float v_layer;

void main() {
    gl_Position = a_transform * a_position;
    v_texCoord = a_uv;
    v_texCoord.y = 1.0 - v_texCoord.y;
    v_color = a_color;
    v_layer = a_layer;
}