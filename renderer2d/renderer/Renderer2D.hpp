#pragma once

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

#include "ShaderHandle.hpp"
#include "SpriteBatch.hpp"
#include "SpriteInstance.hpp"
#include "TextureHandle.hpp"
#include "common.hpp"
#include "gl/Shader.hpp"
#include "gl/Texture2D.hpp"

class Renderer2D {
 public:
  Renderer2D() = default;
  ~Renderer2D() = default;

  void viewport(int x, int y, int width, int height) const {
    glViewport(x, y, width, height);
  }

  void beginFrame() {
    for (auto& batch : _batches) {
      batch.second.flush();
    }
  }

  void endFrame() {
    // shader.bind();
    // vao.bind();
    // tex.bindToSlot(0);
    // shader.uniform("u_texture", 0);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
    // vao.unbind();
    // shader.unbind();
  }

  void drawSprite(const SpriteInstance& sprite, TextureHandle tex) {
    auto batch = _batches.find(tex);
    if (batch == _batches.end()) {
      auto texture = _textures.find(tex);
      if (texture != _textures.end()) {
        SpriteBatch newBatch;
        newBatch.initialize();
        newBatch.setTexture(&texture->second);
        _batches.emplace(tex, std::move(newBatch));
      } else {
        throw std::runtime_error("Error: Use of untracked TextureHandle");
      }
    }
  }

  TextureHandle createTexture(int width, int height, void* data) {
    TextureHandle handle;
    handle.id = _nextTextureId++;
    handle.type = TextureHandle::Type::_2D;

    gl::Texture2D tex;
    tex.initialize(width, height);
    tex.setData(data);

    _textures.emplace(handle, std::move(tex));

    return handle;
  }

  ShaderHandle createShader(const std::string& vertex, const std::string& fragment) {
    ShaderHandle handle;
    handle.id = _nextShaderId++;

    gl::Shader shader;
    shader.initialize();
    shader.loadShader(vertex, fragment);
  }

  ShaderHandle createShaderFromFiles(const std::filesystem::path& vertex, const std::filesystem::path& fragment) {
    ShaderHandle handle;
    handle.id = _nextShaderId++;

    gl::Shader shader;
    shader.initialize();
    shader.bind();
    shader.loadShader(vertex, fragment);
    shader.unbind();
  }

 private:
  std::unordered_map<TextureHandle, gl::Texture2D> _textures;
  std::unordered_map<ShaderHandle, gl::Shader> _shaders;
  std::unordered_map<TextureHandle, SpriteBatch> _batches;

  uint32_t _nextTextureId = 1;
  uint32_t _nextShaderId = 1;
};