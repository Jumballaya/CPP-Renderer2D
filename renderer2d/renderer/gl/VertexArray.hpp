#pragma once

#include <cstdint>
#include <vector>

#include "../common.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"

namespace gl {
struct VertexArray {
 public:
  VertexArray() = default;

  ~VertexArray() {
    if (isValid()) {
      glDeleteVertexArrays(1, &_vao);
    }
  }

  VertexArray(VertexArray&) noexcept = delete;
  VertexArray& operator=(VertexArray&) noexcept = delete;

  VertexArray(VertexArray&& other) noexcept
      : _vao(other._vao), _vbo(std::move(other._vbo)), _ibo(std::move(other._ibo)) {
    other._vao = 0;
  }

  VertexArray& operator=(VertexArray&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    _vao = other._vao;
    _ibo = std::move(other._ibo);
    _vbo = std::move(other._vbo);
    other._vao = 0;
    return *this;
  }

  void initialize() {
    glGenVertexArrays(1, &_vao);
    _vbo.initialize();
    _ibo.initialize();
  }

  void setIndexData(std::vector<uint16_t>& data) {
    bind();
    _ibo.setData(data);
  }

  void setVertexData(std::vector<float>& data) {
    bind();
    _vbo.setData(data);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)(sizeof(float) * 3));
  }

  bool isValid() const {
    return _vao != 0;
  }

  void bind() {
    if (_vao) {
      glBindVertexArray(_vao);
      return;
    }
    unbind();
  }

  void unbind() {
    glBindVertexArray(0);
  }

 private:
  GLuint _vao;
  VertexBuffer _vbo;
  IndexBuffer _ibo;
};
}