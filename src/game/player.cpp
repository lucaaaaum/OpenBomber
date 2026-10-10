#include "game/player.h"
#include <algorithm>

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
  resetMoveCooldown();
}

Direction Player::getDirection() const { return direction; }
float Player::getMoveCooldown() const { return moveCooldown; }
float Player::getBombCooldown() const { return bombCooldown; }

void Player::resetMoveCooldown() { moveCooldown = MOVE_COOLDOWN; }
void Player::resetBombCooldown() { bombCooldown = BOMB_COOLDOWN; }

void Player::updateCooldown(float dt) {
  moveCooldown = std::max(0.0f, moveCooldown - dt);
  bombCooldown = std::max(0.0f, bombCooldown - dt);
}
bool Player::canMove() const { return moveCooldown <= 0; }
bool Player::canPlaceBomb() const { return bombCooldown <= 0; }
