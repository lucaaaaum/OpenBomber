#pragma once

#include "game/fire.h"
#include "game/hitbox.h"
#include <glm/glm.hpp>
#include <vector>

class Player;

class Bomb {
private:
  const Player *owner;
  glm::vec2 position;
  float timer{3.0f};
  int size{1};
  Hitbox hitbox;

public:
  Bomb(const Player *owner, glm::vec2 position);

  const Player *getOwner() const;
  glm::vec2 getPosition() const;
  Hitbox getHitbox() const;
  void update(float dt);
  bool hasExploded() const;
  std::vector<Fire> explode();
};
