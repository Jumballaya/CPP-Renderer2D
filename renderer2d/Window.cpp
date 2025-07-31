#include "Window.hpp"

Window::~Window() {
  if (_window) {
    glfwDestroyWindow(_window);
  }
}

bool Window::initialize(int width, int height, const std::string& title) {
  if (!glfwInit()) {
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  _window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!_window) {
    return false;
  }

  glfwMakeContextCurrent(_window);
  glfwSetWindowUserPointer(_window, this);
  glfwSetFramebufferSizeCallback(_window, handleResize);

  if (!gladLoadGL(glfwGetProcAddress)) {
    return false;
  }

  _width = width;
  _height = height;

  return true;
}

void Window::pollEvents() {
  glfwPollEvents();
}

void Window::swapBuffers() {
  glfwSwapBuffers(_window);
}

bool Window::shouldClose() const {
  return glfwWindowShouldClose(_window);
}

void Window::setResizeCallback(ResizeCallback callback) {
  _resizeCallback = std::move(callback);
}

void Window::handleResize(GLFWwindow* win, int width, int height) {
  auto* self = static_cast<Window*>(glfwGetWindowUserPointer(win));
  if (self) {
    self->_width = width;
    self->_height = height;
    glViewport(0, 0, width, height);
    if (self->_resizeCallback) {
      self->_resizeCallback(width, height);
    }
  }
}