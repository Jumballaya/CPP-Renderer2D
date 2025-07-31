#pragma once

#include <glm/glm.hpp>

struct SpriteInstance {
  glm::mat4 transform;
  glm::vec4 color;
  glm::vec4 texRect;  // [u, v, w, h] -> atlas rect for the sprite, for Texture2D
  float layer;        // Layer for a Texture2DArray, default to 0
};
