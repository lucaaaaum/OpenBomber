#pragma once

#include "game/bomb.h"
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
  std::vector<Bomb> bombs;
  std::vector<Fire> fires;
  void handleMovement(float dt);
  void handleBombPlacement();
  void updateBombs(float dt);
  void updateFires(float dt);
  int countPlayerBombs(const Player &player) const;

public:
  Game(Controller &controller, Renderer &renderer);
  void run();
  const Map &getMap() const;
  const std::vector<Player> &getPlayers() const;
  const std::vector<Bomb> &getBombs() const;
  const std::vector<Fire> &getFires() const;
};
