#include "Application.hpp"

#include <iostream>

Application::~Application() {
  glfwTerminate();
}

void Application::update() {
  _window.swapBuffers();
  _window.pollEvents();
}

bool Application::initialize() {
  _window.initialize(800, 600, "2D Renderer");

  _window.setResizeCallback([](int w, int h) {
    std::cout << "Window resized: " << w << " x " << h << "\n";
  });

  return true;
}

bool Application::shouldClose() const {
  return _window.shouldClose();
}