#pragma once

#include "game/bomb.h"
#include "game/controller.h"
#include "game/enemy.h"
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
  std::vector<Enemy> enemies;
  void handleMovement(float dt);
  void handleBombPlacement();
  void updateBombs(float dt);
  void updateFires(float dt);
  void updateEnemies(float dt);
  int countPlayerBombs(const Player &player) const;
  void handleFireCollisions();
  void handleEnemyCollisions();
  void reset();

public:
  Game(Controller &controller, Renderer &renderer);
  void run();
  const Map &getMap() const;
  const std::vector<Player> &getPlayers() const;
  const std::vector<Bomb> &getBombs() const;
  const std::vector<Fire> &getFires() const;
  const std::vector<Enemy> &getEnemies() const;
};
