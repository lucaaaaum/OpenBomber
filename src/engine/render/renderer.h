#pragma once

#include "engine/render/sprite.h"
#include <GLFW/glfw3.h>
#include <vector>

class Renderer {
private:
  glm::vec2 windowSize;
  std::vector<Sprite> sprites;
  GLFWwindow *window;

public:
  int getWindowWidth() const;
  int getWindowHeight() const;
  void init();
  void render();
};
