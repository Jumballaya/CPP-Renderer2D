#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "../common.hpp"

namespace gl {

struct Texture2D {
 public:
  Texture2D() = default;
  ~Texture2D() {
    if (isValid()) {
      glDeleteTextures(1, &_texture);
    }
  }

  Texture2D(const Texture2D&) noexcept = delete;
  Texture2D& operator=(const Texture2D&) noexcept = delete;

  Texture2D(Texture2D&& other) noexcept
      : _texture(other._texture), _width(other._width), _height(other._height), _internalFormat(other._internalFormat) {
    other._texture = 0;
    other._width = 0;
    other._height = 0;
    other._internalFormat = GL_RGBA8;
  }

  Texture2D& operator=(Texture2D&& other) noexcept {
    if (this == &other) return *this;
    if (isValid()) {
      glDeleteTextures(1, &_texture);
    }
    _texture = other._texture;
    _width = other._width;
    _height = other._height;
    _internalFormat = other._internalFormat;
    other._texture = 0;
    other._width = 0;
    other._height = 0;
    other._internalFormat = GL_RGBA8;
    return *this;
  }

  void initialize(GLsizei width, GLsizei height, GLint internalFormat = GL_RGBA8) {
    glGenTextures(1, &_texture);
    _width = width;
    _height = height;
    _internalFormat = internalFormat;

    bindToSlot(0);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }

  void setData(const std::vector<uint8_t>& data, GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE) {
    bindToSlot(0);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, format, type, data.data());
  }

  void bindToSlot(GLuint slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, _texture);
  }

  bool isValid() {
    return _texture != 0;
  }

  GLuint id() const {
    return _texture;
  }

 private:
  GLuint _texture = 0;
  GLsizei _width = 0;
  GLsizei _height = 0;
  GLint _internalFormat = GL_RGBA8;
};

}  // namespace gl