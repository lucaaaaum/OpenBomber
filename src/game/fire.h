#pragma once

#include <glm/glm.hpp>

class Fire {
private:
  glm::vec2 position;
  float duration{1.0f};

public:
  Fire(glm::vec2 position);

  glm::vec2 getPosition() const;
  void update(float dt);
  bool isExpired() const;
};
