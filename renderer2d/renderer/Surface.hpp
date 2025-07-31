#pragma once

#include <utility>

#include "gl/FrameBuffer.hpp"
#include "gl/Texture2D.hpp"

struct Surface {
  Surface() = default;
  ~Surface() = default;

  Surface(const Surface&) noexcept = delete;
  Surface& operator=(const Surface&) noexcept = delete;

  Surface(Surface&& other) noexcept
      : frameBuffer(std::move(other.frameBuffer)), width(other.width), height(other.height) {
    other.width = 0;
    other.height = 0;
  }

  Surface& operator=(Surface&& other) noexcept {
    frameBuffer = std::move(other.frameBuffer);
    width = other.width;
    height = other.height;
  }

  void initialize(int w, int h) {
    width = w;
    height = h;
    frameBuffer.initialize(w, h);
  }

  void bind() {
    frameBuffer.bind();
  }

  void unbind() {
    frameBuffer.unbind();
  }

  gl::FrameBuffer frameBuffer;

  int width = 0;
  int height = 0;
};