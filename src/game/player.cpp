#include "game/player.h"

Player::Player(glm::vec2 position, Direction direction)
    : position(position), direction(direction) {}

glm::vec2 Player::getPosition() const { return position; }

void Player::move(const glm::vec2 &delta) {
  position += delta;
  if (delta.x > 0) {
    direction = Direction::RIGHT;
  } else if (delta.x < 0) {
    direction = Direction::LEFT;
  } else if (delta.y > 0) {
    direction = Direction::DOWN;
  } else if (delta.y < 0) {
    direction = Direction::UP;
  }
}

Direction Player::getDirection() const { return direction; }
