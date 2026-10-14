#include "game/game.h"
#include "game/controller.h"
#include "game/map.h"
#include "game/player.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>

Game::Game(Controller &controller, Renderer &renderer)
    : controller(controller), renderer(renderer), map(19, 19) {
  auto player = Player(glm::vec2(1.0f, 1.0f));
  players.push_back(player);

  auto &emptyPositions = map.getEmptyTilePositions();
  auto pickedPositions = std::vector<glm::vec2>();
  for (int i = 0; i < 5; ++i) {
    int randomIndex = rand() % emptyPositions.size();
    auto randomPosition = emptyPositions[randomIndex];
    if (std::find(pickedPositions.begin(), pickedPositions.end(),
                  randomPosition) != pickedPositions.end()) {
      --i;
      continue;
    }
    pickedPositions.push_back(randomPosition);
    auto enemy = Enemy(randomPosition);
    enemies.push_back(enemy);
  }
}

void Game::run() {
  auto previous_time = std::chrono::steady_clock::now();
  while (true) {
    auto now = std::chrono::steady_clock::now();
    float dt = std::chrono::duration<float>(now - previous_time).count();
    previous_time = now;

    controller.update();
    if (controller.isDown(ControllerAction::QUIT)) {
      break;
    }

    updateBombs(dt);
    updateFires(dt);
    updateEnemies(dt);
    handleMovement(dt);
    handleFireCollisions();
    handleEnemyCollisions();
    handleBombPlacement();

    renderer.draw(*this);

    auto allPlayersAreDead =
        std::all_of(players.begin(), players.end(),
                    [](const Player &player) { return player.getIsDead(); });
    if (allPlayersAreDead) {
      reset();
    }
  }
}

void Game::updateBombs(float dt) {
  for (auto &bomb : bombs) {
    bomb.update(dt);
    if (bomb.hasExploded()) {
      auto newFires = bomb.explode();
      for (auto &fire : newFires) {
        auto firePosition = fire.getPosition();
        int x = std::floor(firePosition.x);
        int y = std::floor(firePosition.y);
        auto tile = map.getTile(x, y);
        if (!tile || tile->getType() == MapTileType::UNBREAKABLE_WALL) {
          continue;
        }
        fires.insert(fires.end(), fire);
        if (tile && tile->getType() == MapTileType::BREAKABLE_WALL) {
          tile->setType(MapTileType::EMPTY);
        }
      }
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

void Game::updateEnemies(float dt) {
  for (auto &enemy : enemies) {
    auto direction = enemy.getDirection();
    glm::vec2 directionVector(0.0f, 0.0f);
    switch (direction) {
    case Direction::UP:
      directionVector.y -= 1.0f;
      break;
    case Direction::DOWN:
      directionVector.y += 1.0f;
      break;
    case Direction::LEFT:
      directionVector.x -= 1.0f;
      break;
    case Direction::RIGHT:
      directionVector.x += 1.0f;
      break;
    }

    auto nextPosition =
        enemy.getPosition() + directionVector * enemy.getSpeed() * dt;
    auto nextPositionHitbox = enemy.projectHitbox(nextPosition);

    int startingRow = floor(nextPositionHitbox.getMin().y);
    int endingRow = floor(nextPositionHitbox.getMax().y);
    int startingColumn = floor(nextPositionHitbox.getMin().x);
    int endingColumn = floor(nextPositionHitbox.getMax().x);

    for (int row = startingRow; row <= endingRow; ++row) {
      for (int column = startingColumn; column <= endingColumn; ++column) {
        auto tile = map.getTile(column, row);
        if (!tile || tile->getType() == MapTileType::EMPTY) {
          continue;
        }
        auto tileHitbox = map.getTileHitbox(column, row);
        if (nextPositionHitbox.intersects(tileHitbox)) {
          enemy.invertDirection();
          return;
        }
      }
    }

    auto currentHitbox = enemy.getHitbox();
    for (auto &bomb : bombs) {
      auto bombHitbox = bomb.getHitbox();
      auto alreadyInsideBomb = currentHitbox.intersects(bombHitbox);
      if (!alreadyInsideBomb && nextPositionHitbox.intersects(bombHitbox)) {
        enemy.invertDirection();
        return;
      }
    }

    enemy.setPosition(nextPosition);
  }
}

glm::vec2 getDirectionVector(Controller &controller);

void Game::handleMovement(float dt) {
  auto directionVector = getDirectionVector(controller);

  if (directionVector.x == 0.0f && directionVector.y == 0.0f) {
    return;
  }

  auto &player = players[0];

  Direction newDirection;
  if (directionVector.x > 0.0f) {
    newDirection = Direction::RIGHT;
  } else if (directionVector.x < 0.0f) {
    newDirection = Direction::LEFT;
  } else if (directionVector.y > 0.0f) {
    newDirection = Direction::DOWN;
  } else {
    newDirection = Direction::UP;
  }
  player.setDirection(newDirection);

  auto nextPosition =
      player.getPosition() + directionVector * player.getSpeed() * dt;
  auto nextPositionHitbox = player.projectHitbox(nextPosition);

  int startingRow = floor(nextPositionHitbox.getMin().y);
  int endingRow = floor(nextPositionHitbox.getMax().y);
  int startingColumn = floor(nextPositionHitbox.getMin().x);
  int endingColumn = floor(nextPositionHitbox.getMax().x);

  for (int row = startingRow; row <= endingRow; ++row) {
    for (int column = startingColumn; column <= endingColumn; ++column) {
      auto tile = map.getTile(column, row);
      if (!tile || tile->getType() == MapTileType::EMPTY) {
        continue;
      }
      auto tileHitbox = map.getTileHitbox(column, row);
      if (nextPositionHitbox.intersects(tileHitbox)) {
        return;
      }
    }
  }

  auto currentHitbox = player.getHitbox();
  for (auto &bomb : bombs) {
    auto bombHitbox = bomb.getHitbox();
    auto alreadyInsideBomb = currentHitbox.intersects(bombHitbox);
    if (!alreadyInsideBomb && nextPositionHitbox.intersects(bombHitbox)) {
      return;
    }
  }

  player.setPosition(nextPosition);
}

glm::vec2 getDirectionVector(Controller &controller) {
  glm::vec2 direction(0.0f, 0.0f);
  if (controller.isDown(ControllerAction::MOVE_UP)) {
    direction.y -= 1.0f;
  }
  if (controller.isDown(ControllerAction::MOVE_DOWN)) {
    direction.y += 1.0f;
  }
  if (controller.isDown(ControllerAction::MOVE_LEFT)) {
    direction.x -= 1.0f;
  }
  if (controller.isDown(ControllerAction::MOVE_RIGHT)) {
    direction.x += 1.0f;
  }
  if (direction.x == 0.0f && direction.y == 0.0f) {
    return direction;
  }
  return glm::normalize(direction);
}

void Game::handleFireCollisions() {
  for (auto &fire : fires) {
    auto fireHitbox = fire.getHitbox();

    for (auto &player : players) {
      if (player.getIsDead()) {
        continue;
      }
      auto playerHitbox = player.getHitbox();
      if (playerHitbox.intersects(fireHitbox)) {
        player.kill();
        break;
      }
    }
  }

  enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                               [this](const Enemy &enemy) {
                                 auto enemyHitbox = enemy.getHitbox();
                                 return std::any_of(
                                     fires.begin(), fires.end(),
                                     [&enemyHitbox](const Fire &fire) {
                                       return enemyHitbox.intersects(
                                           fire.getHitbox());
                                     });
                               }),
                enemies.end());
}

void Game::handleEnemyCollisions() {
  for (auto &enemy : enemies) {
    auto enemyHitbox = enemy.getHitbox();

    for (auto &player : players) {
      if (player.getIsDead()) {
        continue;
      }
      auto playerHitbox = player.getHitbox();
      if (playerHitbox.intersects(enemyHitbox)) {
        player.kill();
        break;
      }
    }
  }
}

void Game::handleBombPlacement() {
  auto &player = players[0];
  auto playerCanPlaceBomb =
      player.getMaxBombs() > countPlayerBombs(player) && !player.getIsDead();
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
const std::vector<Enemy> &Game::getEnemies() const { return enemies; }

int Game::countPlayerBombs(const Player &player) const {
  return std::count_if(bombs.begin(), bombs.end(), [&player](const Bomb &bomb) {
    return bomb.getOwner() == &player;
  });
}

void Game::reset() {
  map = Map(19, 19);
  players.clear();
  bombs.clear();
  fires.clear();

  auto player = Player(glm::vec2(1.0f, 1.0f));
  players.push_back(player);

  auto &emptyPositions = map.getEmptyTilePositions();
  auto pickedPositions = std::vector<glm::vec2>();
  for (int i = 0; i < 5; ++i) {
    int randomIndex = rand() % emptyPositions.size();
    auto randomPosition = emptyPositions[randomIndex];
    if (std::find(pickedPositions.begin(), pickedPositions.end(),
                  randomPosition) != pickedPositions.end()) {
      --i;
      continue;
    }
    pickedPositions.push_back(randomPosition);
    auto enemy = Enemy(randomPosition);
    enemies.push_back(enemy);
  }
}
