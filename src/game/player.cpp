#include "game/player.h"
#include "game/bomb.h"

Hitbox createHitbox(glm::vec2 position);

Player::Player(glm::vec2 position, Direction direction)
    : position(position), direction(direction), hitbox(createHitbox(position)) {
}

glm::vec2 Player::getPosition() const { return position; }

void Player::setPosition(const glm::vec2 &newPosition) {
  position = newPosition;
  hitbox = createHitbox(newPosition);
}

Hitbox createHitbox(glm::vec2 position) {
  const auto margin = glm::vec2(0.1f, 0.1f);
  return Hitbox(position + margin, position + glm::vec2(1.0f, 1.0f) - margin);
}

Hitbox Player::getHitbox() const { return hitbox; }

Direction Player::getDirection() const { return direction; }
void Player::setDirection(Direction newDirection) { direction = newDirection; }

Bomb Player::placeBomb() { return Bomb(this, position); }

int Player::getMaxBombs() const { return maxBombs; }
float Player::getSpeed() const { return speed; };

Hitbox Player::projectHitbox(glm::vec2 position) const {
  return createHitbox(position);
}
