#pragma once

#include "game/hitbox.h"
#include <glm/glm.hpp>

class Fire {
private:
  glm::vec2 position;
  float duration{1.0f};
  Hitbox hitbox;

public:
  Fire(glm::vec2 position);

  glm::vec2 getPosition() const;
  Hitbox getHitbox() const;
  void update(float dt);
  bool isExpired() const;
};
