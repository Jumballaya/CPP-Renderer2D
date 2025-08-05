#pragma once

#include <utility>
#include <vector>

#include "SpriteInstance.hpp"
#include "gl/GLBuffer.hpp"
#include "gl/Texture2D.hpp"
#include "gl/VertexArray.hpp"

// QUAD Data
inline std::vector<float> vertex_data = {
    // X     Y     Z     U     V
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // v0: bottom-left
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // v1: bottom-right
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,    // v2: top-right
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // v0: bottom-left
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,    // v2: top-right
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // v3: top-left
};

class SpriteBatch {
 public:
  SpriteBatch() = default;
  ~SpriteBatch() = default;

  SpriteBatch(const SpriteBatch&) noexcept = delete;
  SpriteBatch& operator=(const SpriteBatch&) noexcept = delete;

  SpriteBatch(SpriteBatch&& other) noexcept
      : _quadVao(std::move(other._quadVao)), _instances(std::move(other._instances)), _boundTexture(other._boundTexture) {
    other._boundTexture = nullptr;
  };

  SpriteBatch& operator=(SpriteBatch&& other) noexcept {
    if (this == &other) {
      return *this;
    }

    _quadVao = std::move(other._quadVao);
    _instances = std::move(other._instances);
    _boundTexture = other._boundTexture;
    other._boundTexture = nullptr;

    return *this;
  }

  void initialize() {
    _quadVao.initialize();
    std::vector<gl::VertexLayout> vertex_layout = {
        {.elementCount = 3,
         .type = GL_FLOAT,
         .normalized = false,
         .offset = 0},
        {.elementCount = 2,
         .type = GL_FLOAT,
         .normalized = false,
         .offset = sizeof(float) * 3}};
    _quadVao.setVertexData(vertex_data, 5 * sizeof(float), vertex_layout);
  }

  void submit(const SpriteInstance& instance) {
    _instances.push_back(instance);
  }

  void setTexture(gl::Texture2D* tex) {
    _boundTexture = tex;
  }

  void flush() {
    _instances.clear();
  }

 private:
  gl::VertexArray _quadVao;
  std::vector<SpriteInstance> _instances;
  gl::Texture2D* _boundTexture = nullptr;
};