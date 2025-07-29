#pragma once

#include "renderer/common.hpp"

class Application {
 public:
  Application() = default;
  ~Application();

  Application(const Application&) noexcept = delete;
  Application(Application&&) noexcept = delete;
  Application& operator=(const Application&) noexcept = delete;
  Application& operator=(Application&&) noexcept = delete;

  bool initialize();
  void update();

  bool shouldClose() const;

 private:
  GLFWwindow* _window;
};