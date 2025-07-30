#include <glad/gl.h>

#include <iostream>
#include <vector>

#include "Application.hpp"
#include "renderer/gl/Shader.hpp"
#include "renderer/gl/Texture2D.hpp"
#include "renderer/gl/VertexArray.hpp"

std::vector<float> vertex_data = {
    // X     Y     Z     U     V
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // v0: bottom-left
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // v1: bottom-right
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,    // v2: top-right
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // v3: top-left
};

std::vector<uint8_t> image{
    255,
    255,
    255,
    255,
    0,
    0,
    0,
    255,
    0,
    0,
    0,
    255,
    255,
    255,
    255,
    255,
};

std::vector<uint16_t> index_data = {0, 1, 2, 0, 2, 3};

int main() {
  Application app;
  if (!app.initialize()) {
    return -1;
  }

  std::filesystem::path fragPath = "assets/shaders/2d-renderer/fragment.glsl";
  std::filesystem::path vertPath = "assets/shaders/2d-renderer/vertex.glsl";

  gl::Texture2D tex;
  tex.initialize(2, 2);
  tex.setData(image);

  gl::Shader shader;
  shader.initialize();
  shader.bind();
  shader.loadShader(vertPath, fragPath);

  gl::VertexArray vao;
  vao.initialize();
  vao.bind();
  vao.setVertexData(vertex_data);
  vao.setIndexData(index_data);
  vao.unbind();

  while (!app.shouldClose()) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.bind();
    vao.bind();
    tex.bindToSlot(0);
    shader.uniform("u_texture", 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
    vao.unbind();
    shader.unbind();

    app.update();
  }
}