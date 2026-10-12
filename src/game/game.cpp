#include "game/game.h"
#include "game/controller.h"
#include "game/map.h"
#include <algorithm>
#include <chrono>
#include <glm/fwd.hpp>

Game::Game(Controller &controller, Renderer &renderer)
    : controller(controller), renderer(renderer), map(19, 19) {
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

    updateBombs(dt);
    updateFires(dt);
    handleMovement();
    handleBombPlacement();

    renderer.draw(*this);
  }
}

void Game::updateBombs(float dt) {
  for (auto &bomb : bombs) {
    bomb.update(dt);
    if (bomb.hasExploded()) {
      auto newFires = bomb.explode();
      fires.insert(fires.end(), newFires.begin(), newFires.end());
    }
  }

  bombs.erase(
      std::remove_if(bombs.begin(), bombs.end(),
                     [](const Bomb &bomb) { return bomb.hasExploded(); }),
      bombs.end());
}

void Game::updateFires(float dt) {
  for (auto &fire : fires) {
    fire.update(dt);
  }

  fires.erase(std::remove_if(fires.begin(), fires.end(),
                             [](const Fire &fire) { return fire.isExpired(); }),
              fires.end());
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
      if (currentTile->getType() == MapTileType::HAS_PLAYER) {
        currentTile->setType(MapTileType::EMPTY);
      }
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
  auto playerCanPlaceBomb = player.getMaxBombs() > countPlayerBombs(player);
  auto playerWantsToPlaceBomb =
      controller.isPressed(ControllerAction::PLACE_BOMB);

  if (playerCanPlaceBomb && playerWantsToPlaceBomb) {
    auto bomb = player.placeBomb();
    bombs.push_back(bomb);
  }
}

const Map &Game::getMap() const { return map; }

const std::vector<Player> &Game::getPlayers() const { return players; }
const std::vector<Bomb> &Game::getBombs() const { return bombs; }
const std::vector<Fire> &Game::getFires() const { return fires; }

int Game::countPlayerBombs(const Player &player) const {
  return std::count_if(bombs.begin(), bombs.end(), [&player](const Bomb &bomb) {
    return bomb.getOwner() == &player;
  });
}
