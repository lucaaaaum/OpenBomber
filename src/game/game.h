#pragma once

#include "game/controller.h"
#include "game/map.h"
#include "game/renderer.h"
#include <glm/glm.hpp>
#include <vector>

class Game {
private:
  Controller &controller;
  Renderer &renderer;
  Map map;
  std::vector<glm::vec2> players;

public:
  Game(Controller &controller, Renderer &renderer);
  void run();
};
