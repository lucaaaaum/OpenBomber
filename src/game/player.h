#pragma once

#include <glm/glm.hpp>

enum class Direction { UP, DOWN, LEFT, RIGHT };

const float MOVE_COOLDOWN = 0.15f;
const float BOMB_COOLDOWN = 1.0f;

class Player {
private:
  glm::vec2 position;
  Direction direction;
  float moveCooldown{0.0f};
  float bombCooldown{0.0f};

public:
  Player(glm::vec2 position = glm::vec2(0.0f, 0.0f),
         Direction direction = Direction::DOWN);

  glm::vec2 getPosition() const;
  void move(const glm::vec2 &delta);

  Direction getDirection() const;
  void setDirection(Direction newDirection);

  float getMoveCooldown() const;
  void resetMoveCooldown();
  float getBombCooldown() const;
  void resetBombCooldown();
  void updateCooldown(float dt);
  bool canMove() const;
  bool canPlaceBomb() const;
};
