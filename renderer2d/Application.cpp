#include "Application.hpp"

#include <iostream>

Application::~Application() {
  if (_window) {
    glfwDestroyWindow(_window);
  }
  glfwTerminate();
}

void Application::update() {
  glfwSwapBuffers(_window);
  glfwPollEvents();
}

bool Application::initialize() {
  if (!glfwInit()) {
    std::cerr << "GLFW failed to init\n";
    return false;
  }

  _window = glfwCreateWindow(800, 600, "GLAD v2 works!", nullptr, nullptr);
  if (!_window) {
    std::cerr << "GLFW window creation failed\n";
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(_window);

  if (!gladLoadGL(glfwGetProcAddress)) {
    std::cerr << "Glad failed to load OpenGL\n";
    glfwDestroyWindow(_window);
    glfwTerminate();
    return false;
  }

  std::cout << "OpenGL version loaded: " << glGetString(GL_VERSION) << "\n";
  return true;
}

bool Application::shouldClose() const {
  if (!_window) {
    return true;
  }
  return glfwWindowShouldClose(_window);
}