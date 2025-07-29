#include <glad/gl.h>

#include <iostream>

#include "Application.hpp"

int main() {
  Application app;
  if (!app.initialize()) {
    return -1;
  }

  while (!app.shouldClose()) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    app.update();
  }
}