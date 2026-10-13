#include "game/fire.h"

Fire::Fire(glm::vec2 position)
    : position(position), hitbox(position, position + glm::vec2(1.0f, 1.0f)) {}

glm::vec2 Fire::getPosition() const { return position; }

Hitbox Fire::getHitbox() const { return hitbox; }

void Fire::update(float dt) { duration -= dt; }

bool Fire::isExpired() const { return duration <= 0.0f; }
