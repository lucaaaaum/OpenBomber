#include "game/bomb.h"

Bomb::Bomb(glm::vec2 position) : position(position) {}

glm::vec2 Bomb::getPosition() const { return position; }

void Bomb::update(float dt) { timer -= dt; }

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
