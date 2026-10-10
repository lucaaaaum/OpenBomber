#pragma once

#include "game/renderer.h"

struct GLFWwindow;

class GlRenderer : public Renderer {
private:
  GLFWwindow *window;

public:
  explicit GlRenderer(GLFWwindow *window);
  void draw(const Game &game) override;
};
