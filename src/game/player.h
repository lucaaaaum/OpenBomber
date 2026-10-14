#pragma once

#include "game/bomb.h"
#include "game/hitbox.h"
#include <glm/glm.hpp>

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Player {
private:
  float speed{4.0f};
  glm::vec2 position;
  Direction direction;
  bool isMoving{false};
  float animationTimer{0.0f};
  int maxBombs{1};
  int bombSize{1};
  Hitbox hitbox;
  bool isDead{false};

public:
  Player(glm::vec2 position = glm::vec2(0.0f, 0.0f),
         Direction direction = Direction::DOWN);

  glm::vec2 getPosition() const;
  void setPosition(const glm::vec2 &newPosition);

  Direction getDirection() const;
  void setDirection(Direction newDirection);

  bool getIsMoving() const;
  void setIsMoving(bool newIsMoving);

  void updateAnimation(float dt);
  int getAnimationFrame() const;

  Bomb placeBomb();
  int getMaxBombs() const;
  void setMaxBombs(int newMaxBombs);

  float getSpeed() const;

  Hitbox getHitbox() const;

  Hitbox projectHitbox(glm::vec2 position) const;

  bool getIsDead() const;
  void kill();
};
