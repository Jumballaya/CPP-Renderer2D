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

  return true;
}

Window& Application::window() {
  return _window;
}

bool Application::shouldClose() const {
  return _window.shouldClose();
}