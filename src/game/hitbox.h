#pragma once

#include <glm/glm.hpp>

class Hitbox {
private:
  glm::vec2 min;
  glm::vec2 max;

public:
  Hitbox(glm::vec2 min, glm::vec2 max);

  glm::vec2 getMin() const;
  void setMin(const glm::vec2 &newMin);
  glm::vec2 getMax() const;
  void setMax(const glm::vec2 &newMax);

  bool intersects(const Hitbox &other) const;
};
