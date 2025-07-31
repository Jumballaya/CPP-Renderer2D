#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "../common.hpp"
#include "GLBuffer.hpp"

namespace gl {

struct VertexLayout {
  int elementCount;
  GLenum type;
  bool normalized;
  int offset;
};

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
    _vbo.initialize(gl::BufferType::Vertex);
    _ibo.initialize(gl::BufferType::Index);
  }

  void setIndexData(std::vector<uint16_t>& data) {
    bind();
    _ibo.setData(data.data(), data.size() * sizeof(uint16_t));
  }

  void setVertexData(std::vector<float>& data, int stride, std::vector<VertexLayout>& layout) {
    bind();
    _vbo.setData(data.data(), data.size() * sizeof(float));

    int offset = 0;
    for (int i = 0; i < layout.size(); ++i) {
      auto& vl = layout[i];
      glEnableVertexAttribArray(i);
      glVertexAttribPointer(i, vl.elementCount, vl.type, vl.normalized, stride, (void*)vl.offset);
    }
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
  GLBuffer _vbo;
  GLBuffer _ibo;
};
}  // namespace gl