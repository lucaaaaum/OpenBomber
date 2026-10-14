#include "game/enemy.h"

Enemy::Enemy(glm::vec2 position) : hitbox(position, glm::vec2(0.5f, 0.5f)) {

  int randomDirection = rand() % 4;
  switch (randomDirection) {
  case 0:
    this->direction = Direction::UP;
    break;
  case 1:
    this->direction = Direction::DOWN;
    break;
  case 2:
    this->direction = Direction::LEFT;
    break;
  case 3:
    this->direction = Direction::RIGHT;
    break;
  }
}

glm::vec2 Enemy::getPosition() const { return hitbox.getMin(); }

void Enemy::setPosition(const glm::vec2 &newPosition) {
  hitbox.setMin(newPosition);
  hitbox.setMax(newPosition + glm::vec2(0.5f, 0.5f));
}

Direction Enemy::getDirection() const { return direction; }

void Enemy::setDirection(Direction newDirection) { direction = newDirection; }

float Enemy::getSpeed() const { return speed; }

Hitbox Enemy::getHitbox() const { return hitbox; }

Hitbox Enemy::projectHitbox(glm::vec2 position) const {
  return Hitbox(position, position + glm::vec2(0.5f, 0.5f));
}
void Enemy::invertDirection() {
  if (direction == Direction::UP) {
    direction = Direction::DOWN;
  } else if (direction == Direction::DOWN) {
    direction = Direction::UP;
  } else if (direction == Direction::LEFT) {
    direction = Direction::RIGHT;
  } else if (direction == Direction::RIGHT) {
    direction = Direction::LEFT;
  }
}
