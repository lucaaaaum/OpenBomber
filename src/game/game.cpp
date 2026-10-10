#include "game/game.h"
#include "game/controller.h"
#include "game/map.h"
#include <glm/fwd.hpp>

Game::Game(Controller &controller, Renderer &renderer)
    : controller(controller), renderer(renderer), map(30, 10) {
  auto player = Player(glm::vec2(1.0f, 1.0f));
  players.push_back(player);
}

void Game::run() {
  while (true) {
    controller.update();
    if (controller.isDown(ControllerAction::QUIT)) {
      break;
    }

    handleMovement();
    handleBombPlacement();

    renderer.draw(*this);
  }
}

glm::vec2 getNextPositionDelta(Controller &controller);

void preventDiagonalMovement(glm::vec2 &delta);

void Game::handleMovement() {
  auto delta = getNextPositionDelta(controller);
  preventDiagonalMovement(delta);

  if (delta.x != 0.0f || delta.y != 0.0f) {
    auto &player = players[0];
    auto playerPosition = player.getPosition();
    auto nextPosition =
        glm::vec2(playerPosition.x + delta.x, playerPosition.y + delta.y);
    auto *nextTile = map.getTile(nextPosition.x, nextPosition.y);
    if (nextTile != nullptr && nextTile->getType() == MapTileType::EMPTY) {
      player.move(delta);
      auto *currentTile = map.getTile(playerPosition.x, playerPosition.y);
      currentTile->setType(MapTileType::EMPTY);
      nextTile->setType(MapTileType::HAS_PLAYER);
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

void Game::handleBombPlacement() {
  if (controller.isPressed(ControllerAction::PLACE_BOMB)) {
    auto &player = players[0];
    auto playerPosition = player.getPosition();
    auto *tile = map.getTile(playerPosition.x, playerPosition.y);
    if (tile != nullptr && tile->getType() == MapTileType::HAS_PLAYER) {
      tile->setType(MapTileType::BOMB);
    }
  }
}

Map &Game::getMap() { return map; }

const std::vector<Player> &Game::getPlayers() const { return players; }
