#pragma once

#include "game/fire.h"
#include <glm/glm.hpp>
#include <vector>

class Bomb {
private:
  glm::vec2 position;
  float timer{3.0f};
  int size{1};

public:
  Bomb(glm::vec2 position);

  glm::vec2 getPosition() const;
  void update(float dt);
  bool hasExploded() const;
  std::vector<Fire> explode();
};
