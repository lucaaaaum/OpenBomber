#include "render/sprite.h"

Sprite::Sprite(float width, float height, unsigned int textureId)
    : size(width, height), textureId(textureId) {}

float Sprite::getWidth() {
    return size.x;
}

float Sprite::getHeight() {
    return size.y;
}