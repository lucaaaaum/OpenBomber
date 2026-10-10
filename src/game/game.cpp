#include "game/game.h"
#include "game/controller.h"
#include "game/map.h"
#include <chrono>
#include <glm/fwd.hpp>

Game::Game(Controller &controller, Renderer &renderer)
    : controller(controller), renderer(renderer), map(30, 10) {
  auto player = Player(glm::vec2(1.0f, 1.0f));
  players.push_back(player);
}

void Game::run() {
  auto previous_time = std::chrono::steady_clock::now();
  while (true) {
    auto now = std::chrono::steady_clock::now();
    float dt = std::chrono::duration<float>(now - previous_time).count();
    previous_time = now;

    for (auto &player : players) {
      player.updateCooldown(dt);
    }

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
    if (!player.canMove()) {
      return;
    }

    auto playerPosition = player.getPosition();
    auto nextPosition =
        glm::vec2(playerPosition.x + delta.x, playerPosition.y + delta.y);
    auto *nextTile = map.getTile(nextPosition.x, nextPosition.y);
    if (nextTile != nullptr && nextTile->getType() == MapTileType::EMPTY) {
      player.move(delta);
      player.resetMoveCooldown();
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
  auto &player = players[0];
  if (controller.isPressed(ControllerAction::PLACE_BOMB) &&
      player.canPlaceBomb()) {
    auto playerPosition = player.getPosition();
    auto *tile = map.getTile(playerPosition.x, playerPosition.y);
    if (tile != nullptr && tile->getType() == MapTileType::HAS_PLAYER) {
      tile->setType(MapTileType::BOMB);
      player.resetBombCooldown();
    }
  }
}

Map &Game::getMap() { return map; }

const std::vector<Player> &Game::getPlayers() const { return players; }
