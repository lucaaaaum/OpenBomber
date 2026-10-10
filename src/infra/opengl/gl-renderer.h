#pragma once

#include "game/renderer.h"

struct GLFWwindow;

class GlRenderer : public Renderer {
private:
  GLFWwindow *window;
  unsigned int shaderProgram;
  unsigned int vbo;
  unsigned int vao;
  void createShaderProgram();

public:
  explicit GlRenderer(GLFWwindow *window);
  ~GlRenderer() override;
  void draw(const Game &game) override;
};
