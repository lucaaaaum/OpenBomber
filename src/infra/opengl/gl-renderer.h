#pragma once

#include "game/map.h"
#include "game/player.h"
#include "game/renderer.h"
#include "infra/opengl/sprite.h"
#include <map>
#include <vector>

struct GLFWwindow;

class GlRenderer : public Renderer {
private:
  GLFWwindow *window;
  unsigned int shaderProgram;
  unsigned int vbo;
  unsigned int vao;
  std::map<MapTileType, Sprite> tileSprites;
  Sprite playerSprite;
  void createShaderProgram();
  void loadSprites();
  void drawMap(const Map &map);
  void drawPlayers(const std::vector<Player> &players);

public:
  explicit GlRenderer(GLFWwindow *window);
  ~GlRenderer() override;
  void draw(const Game &game) override;
};
