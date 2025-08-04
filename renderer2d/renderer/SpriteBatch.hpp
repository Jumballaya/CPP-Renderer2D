#pragma once

#include <utility>
#include <vector>

#include "SpriteInstance.hpp"
#include "gl/GLBuffer.hpp"
#include "gl/Texture2D.hpp"
#include "gl/VertexArray.hpp"

class SpriteBatch {
 public:
  SpriteBatch() = default;
  ~SpriteBatch() = default;

  SpriteBatch(const SpriteBatch&) noexcept = delete;
  SpriteBatch& operator=(const SpriteBatch&) noexcept = delete;

  SpriteBatch(SpriteBatch&& other) noexcept
      : _vao(std::move(other._vao)), _quadVbo(std::move(other._quadVbo)), _instances(std::move(other._instances)), _boundTexture(other._boundTexture) {
    other._boundTexture = nullptr;
  };

  SpriteBatch& operator=(SpriteBatch&& other) noexcept {
    if (this == &other) {
      return *this;
    }

    _vao = std::move(other._vao);
    _quadVbo = std::move(other._quadVbo);
    _instances = std::move(other._instances);
    _boundTexture = other._boundTexture;
    other._boundTexture = nullptr;

    return *this;
  }

  void begin();
  void submit(const SpriteInstance& instance);
  void flush();
  void setTexture(gl::Texture2D* tex);

 private:
  gl::VertexArray _vao;
  gl::GLBuffer _quadVbo;
  std::vector<SpriteInstance> _instances;
  gl::Texture2D* _boundTexture = nullptr;
};