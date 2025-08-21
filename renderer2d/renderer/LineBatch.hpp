#pragma once

#include <vector>

#include "gl/GLBuffer.hpp"
#include "gl/VertexArray.hpp"

class LineBatch {
 public:
  LineBatch() = default;
  ~LineBatch() = default;

  LineBatch(const LineBatch&) noexcept = delete;
  LineBatch& operator=(const LineBatch&) noexcept = delete;
  LineBatch(LineBatch&& other) noexcept = delete;
  LineBatch& operator=(LineBatch&& other) noexcept = delete;

 private:
  gl::VertexArray _lineVao;
  gl::GLBuffer _lineVbo;
  std::vector<float> _lineVerts;
};
