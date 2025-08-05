#include <glad/gl.h>

#include <iostream>
#include <vector>

#include "../renderer2d/Application.hpp"
#include "../renderer2d/renderer/Renderer2D.hpp"
#include "../renderer2d/renderer/gl/Shader.hpp"
#include "../renderer2d/renderer/gl/Texture2D.hpp"
#include "../renderer2d/renderer/gl/VertexArray.hpp"

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

int main() {
  Application app;
  if (!app.initialize()) {
    return -1;
  }

  Renderer2D renderer;

  auto basicShader = renderer.createShader(
      "assets/shaders/2d-renderer/fragment.glsl",
      "assets/shaders/2d-renderer/vertex.glsl");

  auto defaultTexture = renderer.createTexture(2, 2, image.data());

  while (!app.shouldClose()) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer.beginFrame();

    renderer.drawSprite({.transform = glm::mat4{},
                         .color = {1, 0, 0, 1},
                         .texRect = {0, 0, 1, 1},
                         .layer = 0},
                        defaultTexture);

    renderer.endFrame();

    app.update();
  }
}