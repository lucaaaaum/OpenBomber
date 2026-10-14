#include "game/bomb.h"

Bomb::Bomb(const Player *owner, glm::vec2 position)
    : owner(owner), position(position),
      hitbox(position, position + glm::vec2(1.0f, 1.0f)) {}

const Player *Bomb::getOwner() const { return owner; }

glm::vec2 Bomb::getPosition() const { return position; }

Hitbox Bomb::getHitbox() const { return hitbox; }

void Bomb::update(float dt) { timer -= dt; }

float Bomb::getProgress() const {
  return glm::clamp(1.0f - timer / fuseDuration, 0.0f, 1.0f);
}

bool Bomb::hasExploded() const { return timer <= 0.0f; }

std::vector<Fire> Bomb::explode() {
  std::vector<Fire> fireList;
  fireList.emplace_back(position);
  for (int i = 1; i <= size; ++i) {
    fireList.emplace_back(position + glm::vec2(i, 0));
    fireList.emplace_back(position + glm::vec2(-i, 0));
    fireList.emplace_back(position + glm::vec2(0, i));
    fireList.emplace_back(position + glm::vec2(0, -i));
  }
  return fireList;
}
