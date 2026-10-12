#include "game/fire.h"

Fire::Fire(glm::vec2 position) : position(position) {}

glm::vec2 Fire::getPosition() const { return position; }

void Fire::update(float dt) { duration -= dt; }

bool Fire::isExpired() const { return duration <= 0.0f; }
