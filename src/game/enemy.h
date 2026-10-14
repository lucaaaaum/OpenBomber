#pragma once

#include "game/player.h"

class Enemy {
private:
  float speed{2.0f};
  glm::vec2 position;
  Direction direction;
  Hitbox hitbox;

public:
  Enemy(glm::vec2 position = glm::vec2(0.0f, 0.0f));

  glm::vec2 getPosition() const;
  void setPosition(const glm::vec2 &newPosition);

  Direction getDirection() const;
  void setDirection(Direction newDirection);

  float getSpeed() const;

  Hitbox getHitbox() const;

  Hitbox projectHitbox(glm::vec2 position) const;

  void invertDirection();
};
