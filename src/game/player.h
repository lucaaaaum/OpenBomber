#pragma once

#include <glm/glm.hpp>

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Player {
private:
  glm::vec2 position;
  Direction direction;

public:
  Player(glm::vec2 position = glm::vec2(0.0f, 0.0f),
         Direction direction = Direction::DOWN);

  glm::vec2 getPosition() const;
  void move(const glm::vec2 &delta);

  Direction getDirection() const;
  void setDirection(Direction newDirection);
};
