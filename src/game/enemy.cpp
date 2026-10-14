#include "game/enemy.h"

Hitbox createEnemyHitbox(glm::vec2 position);

Enemy::Enemy(glm::vec2 position)
    : position(position), hitbox(createEnemyHitbox(position)) {

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

Hitbox createEnemyHitbox(glm::vec2 position) {
  const auto margin = glm::vec2(0.1f, 0.1f);
  return Hitbox(position + margin, position + glm::vec2(1.0f, 1.0f) - margin);
}

glm::vec2 Enemy::getPosition() const { return position; }

void Enemy::setPosition(const glm::vec2 &newPosition) {
  position = newPosition;
  hitbox = createEnemyHitbox(newPosition);
}

Direction Enemy::getDirection() const { return direction; }

void Enemy::setDirection(Direction newDirection) { direction = newDirection; }

float Enemy::getSpeed() const { return speed; }

Hitbox Enemy::getHitbox() const { return hitbox; }

Hitbox Enemy::projectHitbox(glm::vec2 position) const {
  return createEnemyHitbox(position);
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
