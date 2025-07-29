#pragma once

#include <vector>

#include "../common.hpp"

struct VertexBuffer {
 public:
  VertexBuffer() = default;

  ~VertexBuffer() {
    if (isValid()) {
      glDeleteBuffers(1, &_id);
    }
  }

  VertexBuffer(VertexBuffer&) noexcept = delete;
  VertexBuffer& operator=(VertexBuffer&) noexcept = delete;

  VertexBuffer(VertexBuffer&& other) noexcept
      : _id(other._id) {
    other._id = 0;
  }

  VertexBuffer& operator=(VertexBuffer&& other) noexcept {
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

  void setData(std::vector<float>& data) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
  }

  bool isValid() const {
    return _id != static_cast<GLuint>(0);
  }

  void bind() {
    if (_id) {
      glBindBuffer(GL_ARRAY_BUFFER, _id);
      return;
    }
    unbind();
  }

  void unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

 private:
  GLuint _id;
};