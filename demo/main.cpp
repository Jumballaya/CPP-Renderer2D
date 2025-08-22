#include <glad/gl.h>

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

#include "../renderer2d/Application.hpp"
#include "../renderer2d/renderer/Renderer2D.hpp"
#include "../renderer2d/renderer/gl/Shader.hpp"
#include "../renderer2d/renderer/gl/Texture2D.hpp"
#include "../renderer2d/renderer/gl/VertexArray.hpp"

glm::mat4 transform(glm::vec3 pos, float rot, glm::vec2 scale) {
  glm::mat4 out(1.0f);
  out = glm::translate(out, pos);
  out = glm::rotate(out, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
  out = glm::scale(out, glm::vec3(scale.x, scale.y, 1.0f));
  return out;
}

int main() {
  Application app;
  if (!app.initialize()) {
    return -1;
  }

  Renderer2D renderer;
  renderer.initialize(800, 600);

  app.window().setResizeCallback([&renderer](int w, int h) {
    std::cout << "Window resized: " << w << " x " << h << "\n";
    renderer.resizeTargets(w, h);
  });

  glm::mat4 t1 = transform(glm::vec3(-90.0f, -90.0f, 0.0f), 0.0f, glm::vec2(20.0f, 20.0f));
  glm::mat4 t2 = transform(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec2(20.0f, 20.0f));
  glm::mat4 t3 = transform(glm::vec3(90.0f, 90.0f, 0.0f), 0.0f, glm::vec2(20.0f, 20.0f));

  while (!app.shouldClose()) {
    renderer.beginFrame();

    renderer.drawSprite(t1, {0, 1, 1, 1}, {0, 0, 1, 1}, 0, renderer.getDefaultTexture());
    renderer.drawSprite(t2, {1, 1, 0, 1}, {0, 0, 1, 1}, 0, renderer.getDefaultTexture());
    renderer.drawSprite(t3, {1, 0, 1, 1}, {0, 0, 1, 1}, 0, renderer.getDefaultTexture());

    renderer.endFrame();

    app.update();
  }
}