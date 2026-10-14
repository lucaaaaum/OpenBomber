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
  float fuseDuration{3.0f};
  float timer{fuseDuration};
  int size{1};
  Hitbox hitbox;

public:
  Bomb(const Player *owner, glm::vec2 position);

  const Player *getOwner() const;
  glm::vec2 getPosition() const;
  Hitbox getHitbox() const;
  void update(float dt);
  float getProgress() const;
  bool hasExploded() const;
  std::vector<Fire> explode();
};
