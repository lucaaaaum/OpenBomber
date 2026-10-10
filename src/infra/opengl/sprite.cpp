#include "infra/opengl/sprite.h"

Sprite::Sprite(char *sourcePath) : sourcePath(sourcePath) {}

float Sprite::getWidth() const { return size.x; }

float Sprite::getHeight() const { return size.y; }

void Sprite::setSize(float width, float height) {
  size = glm::vec2(width, height);
}

void Sprite::setTextureId(unsigned int id) { textureId = id; }
unsigned int Sprite::getTextureId() const { return textureId; }
char *Sprite::getSourcePath() const { return sourcePath; }
