#pragma once

#include "game/controller.h"
#include "game/map.h"
#include "game/player.h"
#include "game/renderer.h"
#include <glm/glm.hpp>
#include <vector>

class Game {
private:
  Controller &controller;
  Renderer &renderer;
  Map map;
  std::vector<Player> players;
  void handleMovement();
  void handleBombPlacement();

public:
  Game(Controller &controller, Renderer &renderer);
  void run();
  Map &getMap();
  const std::vector<Player> &getPlayers() const;
};
