#include "game/hitbox.h"

Hitbox::Hitbox(glm::vec2 min, glm::vec2 max) : min(min), max(max) {}

glm::vec2 Hitbox::getMin() const { return min; }
void Hitbox::setMin(const glm::vec2 &newMin) { min = newMin; }
glm::vec2 Hitbox::getMax() const { return max; }
void Hitbox::setMax(const glm::vec2 &newMax) { max = newMax; }

bool Hitbox::intersects(const Hitbox &other) const {
  return !(max.x <= other.min.x || min.x >= other.max.x ||
           max.y <= other.min.y || min.y >= other.max.y);
}
