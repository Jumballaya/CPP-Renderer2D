#pragma once

#include <cstdint>
#include <vector>

#include "../common.hpp"

struct IndexBuffer {
 public:
  IndexBuffer() = default;

  ~IndexBuffer() {
    if (isValid()) {
      glDeleteBuffers(1, &_id);
    }
  }

  IndexBuffer(IndexBuffer&) noexcept = delete;
  IndexBuffer& operator=(IndexBuffer&) noexcept = delete;

  IndexBuffer(IndexBuffer&& other) noexcept
      : _id(other._id) {
    other._id = 0;
  }

  IndexBuffer& operator=(IndexBuffer&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    _id = other._id;
    other._id = 0;
    return *this;
  }

  void initialize() {
    glGenBuffers(1, &_id);
  }

  void setData(std::vector<uint16_t>& data) {
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(uint16_t), data.data(), GL_STATIC_DRAW);
  }

  bool isValid() const {
    return _id != (GLuint)0;
  }

  void bind() {
    if (_id) {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
      return;
    }
    unbind();
  }

  void unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

 private:
  GLuint _id;
};