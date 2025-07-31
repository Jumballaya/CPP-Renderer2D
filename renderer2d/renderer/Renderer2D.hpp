#pragma once

#include "common.hpp"

class Renderer2D {
 public:
  void viewport(int x, int y, int width, int height) const {
    glViewport(x, y, width, height);
  }

 private:
};