#include <glad/gl.h>

#include <iostream>
#include <vector>

#include "Application.hpp"
#include "renderer/gl/Shader.hpp"
#include "renderer/gl/VertexArray.hpp"

std::vector<float> vertex_data = {
    // X     Y     Z     U     V
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // v0: bottom-left
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // v1: bottom-right
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,    // v2: top-right
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // v3: top-left
};

std::vector<uint16_t> index_data = {0, 1, 2, 0, 2, 3};

int main() {
  Application app;
  if (!app.initialize()) {
    return -1;
  }

  std::filesystem::path fragPath = "assets/shaders/2d-renderer/fragment.glsl";
  std::filesystem::path vertPath = "assets/shaders/2d-renderer/vertex.glsl";

  Shader shader;
  shader.initialize();
  shader.bind();
  shader.loadShader(vertPath, fragPath);

  VertexArray vao;
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
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
    vao.unbind();
    shader.unbind();

    app.update();
  }
}