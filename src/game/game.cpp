#include "game/game.h"
#include "game/controller.h"
#include "game/map.h"
#include <glm/fwd.hpp>

Game::Game(Controller &controller, Renderer &renderer)
    : controller(controller), renderer(renderer), map(30, 10) {}

void Game::run() {
  while (true) {
    controller.update();
    if (controller.isDown(ControllerAction::QUIT)) {
      break;
    }

    handleMovement();

    renderer.draw(*this);
  }
}

glm::vec2 getNextPositionDelta(Controller &controller);

void preventDiagonalMovement(glm::vec2 &delta);

void Game::handleMovement() {
  auto delta = getNextPositionDelta(controller);
  preventDiagonalMovement(delta);

  if (delta.x != 0.0f || delta.y != 0.0f) {
    auto player = players[0];
    auto nextPosition = glm::vec2(player.x + delta.x, player.y + delta.y);
    auto nextTile = map.getTile(nextPosition.x, nextPosition.y);
    if (nextTile.getType() == MapTileType::EMPTY) {
      auto currentTile = map.getTile(player.x, player.y);
      players[0] = nextPosition;
      currentTile.setType(MapTileType::EMPTY);
      nextTile.setType(MapTileType::HAS_PLAYER);
    }
  }
}

glm::vec2 getNextPositionDelta(Controller &controller) {
  glm::vec2 delta(0.0f, 0.0f);
  if (controller.isDown(ControllerAction::MOVE_UP)) {
    delta.y -= 1.0f;
  }
  if (controller.isDown(ControllerAction::MOVE_DOWN)) {
    delta.y += 1.0f;
  }
  if (controller.isDown(ControllerAction::MOVE_LEFT)) {
    delta.x -= 1.0f;
  }
  if (controller.isDown(ControllerAction::MOVE_RIGHT)) {
    delta.x += 1.0f;
  }
  return delta;
}

void preventDiagonalMovement(glm::vec2 &delta) {
  if (delta.y != 0.0f) {
    delta.x = 0.0f;
  }
}

Map &Game::getMap() { return map; }

std::vector<glm::vec2> &Game::getPlayers() { return players; }
