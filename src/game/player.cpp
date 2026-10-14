#include "game/player.h"
#include "game/bomb.h"
#include <cmath>

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

bool Player::getIsMoving() const { return isMoving; }
void Player::setIsMoving(bool newIsMoving) { isMoving = newIsMoving; }

const float ANIMATION_FRAME_DURATION = 0.2f;
const int ANIMATION_FRAME_COUNT = 2;

void Player::updateAnimation(float dt) {
  animationTimer = std::fmod(animationTimer + dt,
                             ANIMATION_FRAME_DURATION * ANIMATION_FRAME_COUNT);
}

int Player::getAnimationFrame() const {
  return static_cast<int>(animationTimer / ANIMATION_FRAME_DURATION) %
         ANIMATION_FRAME_COUNT;
}

Bomb Player::placeBomb() {
  auto bombPosition = glm::floor(position + 0.5f);
  return Bomb(this, bombPosition);
}

int Player::getMaxBombs() const { return maxBombs; }
float Player::getSpeed() const { return speed; };

Hitbox Player::projectHitbox(glm::vec2 position) const {
  return createHitbox(position);
}
void Player::kill() { isDead = true; }

bool Player::getIsDead() const { return isDead; }
