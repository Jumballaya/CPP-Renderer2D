#pragma once

#include <functional>
#include <string>

#include "renderer/common.hpp"

class Window {
 public:
  using ResizeCallback = std::function<void(int, int)>;

  Window() = default;
  ~Window();

  bool initialize(int width, int height, const std::string& title = "Renderer");
  void pollEvents();
  void swapBuffers();
  bool shouldClose() const;

  void setResizeCallback(ResizeCallback callback);
  GLFWwindow* getGLFWWindow();

  int getWidth() const;
  int getHeight() const;

 private:
  GLFWwindow* _window = nullptr;
  ResizeCallback _resizeCallback;
  int _width = 0;
  int _height = 0;

  static void handleResize(GLFWwindow* window, int width, int height);
};