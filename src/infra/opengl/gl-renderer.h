#pragma once

#include "game/map.h"
#include "game/player.h"
#include "game/renderer.h"
#include <vector>

struct GLFWwindow;

class GlRenderer : public Renderer {
private:
  GLFWwindow *window;
  unsigned int shaderProgram;
  unsigned int vbo;
  unsigned int vao;
  void createShaderProgram();
  void drawMap(const Map &map);
  void drawPlayers(const std::vector<Player> &players);

public:
  explicit GlRenderer(GLFWwindow *window);
  ~GlRenderer() override;
  void draw(const Game &game) override;
};
