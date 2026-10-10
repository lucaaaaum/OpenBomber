#pragma once

#include <glm/glm.hpp>

class Sprite {
private:
  glm::vec2 size;
  char *sourcePath;
  unsigned int textureId;

public:
  Sprite(char *sourcePath);
  float getWidth() const;
  float getHeight() const;
  void setSize(float width, float height);
  void setTextureId(unsigned int id);
  unsigned int getTextureId() const;
  char *getSourcePath() const;
};
