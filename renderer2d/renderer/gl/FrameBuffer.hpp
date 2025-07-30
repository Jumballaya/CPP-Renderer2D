#pragma once

#include <utility>

#include "../common.hpp"
#include "Texture2D.hpp"

namespace gl {

struct FrameBuffer {
 public:
  FrameBuffer() = default;

  ~FrameBuffer() {
    if (isValid()) {
      glDeleteFramebuffers(1, &_fbo);
    }
  }

  FrameBuffer(const FrameBuffer&) = delete;
  FrameBuffer& operator=(const FrameBuffer&) = delete;

  FrameBuffer(FrameBuffer&& other) noexcept
      : _fbo(other._fbo), _color(std::move(other._color)), _depth(std::move(other._depth)), _width(other._width), _height(other._height) {
    other._fbo = 0;
    other._width = 0;
    other._height = 0;
  }

  FrameBuffer& operator=(FrameBuffer&& other) noexcept {
    if (this == &other) {
      return *this;
    }

    if (isValid()) {
      glDeleteFramebuffers(1, &_fbo);
    }

    _fbo = other._fbo;
    _color = std::move(other._color);
    _depth = std::move(other._depth);
    _width = other._width;
    _height = other._height;

    other._fbo = 0;
    other._width = 0;
    other._height = 0;

    return *this;
  }

  void initialize(int width, int height) {
    _color.initialize(width, height);
    _depth.initialize(width, height);
  }

  void bind(GLenum target = GL_FRAMEBUFFER) {
    glBindFramebuffer(target, _fbo);
  }

  void unbind() {}

  Texture2D getColorTexture() const {}

  Texture2D getDepthTexture() const {}

  void resize(int newWidth, int newHeight);

  GLuint id() const { return _fbo; }

  bool isValid() const { return _fbo != 0; }

 private:
  GLuint _fbo;
  Texture2D _color;
  Texture2D _depth;
  int _width = 0;
  int _height = 0;
};

}  // namespace gl