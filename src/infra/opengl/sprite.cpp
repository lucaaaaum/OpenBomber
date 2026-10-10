#include "infra/opengl/sprite.h"

Sprite::Sprite(float width, float height, unsigned int textureId)
    : size(width, height), textureId(textureId) {}

float Sprite::getWidth() const { return size.x; }

float Sprite::getHeight() const { return size.y; }
