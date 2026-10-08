#pragma once

#include <glm/glm.hpp>

class Sprite {
private:
    glm::vec2 size;
    unsigned int textureId;

public:
    Sprite(float width, float height, unsigned int textureId);
    float getWidth();
    float getHeight();
};