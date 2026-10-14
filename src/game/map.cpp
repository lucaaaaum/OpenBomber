#include "game/map.h"

MapTile::MapTile(MapTileType type) : type(type) {}

MapTileType MapTile::getType() const { return type; }

Map::Map(int width, int height) : grid(height, std::vector<MapTile>(width)) {
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
        grid[y][x] = MapTile(MapTileType::UNBREAKABLE_WALL);
      } else if (y % 2 == 0 && x % 2 == 0) {
        grid[y][x] = MapTile(MapTileType::UNBREAKABLE_WALL);
      } else {
        grid[y][x] = MapTile(MapTileType::EMPTY);
      }
    }
  }

  for (int y = 1; y < height - 1; ++y) {
    for (int x = 1; x < width - 1; ++x) {
      if ((x == 1 && y == 1) || (x == 1 && y == 2) || (x == 2 && y == 1))
        continue;
      if (grid[y][x].getType() == MapTileType::EMPTY) {
        if (rand() % 100 < 30) {
          grid[y][x] = MapTile(MapTileType::BREAKABLE_WALL);
        }
      }
    }
  }
}

MapTile *Map::getTile(int x, int y) {
  if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight()) {
    return nullptr;
  }
  return &grid[y][x];
}

const MapTile *Map::getTile(int x, int y) const {
  if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight()) {
    return nullptr;
  }
  return &grid[y][x];
}

int Map::getWidth() const { return grid[0].size(); }

int Map::getHeight() const { return grid.size(); }
Hitbox Map::getTileHitbox(int x, int y) const {
  return Hitbox(glm::vec2(x, y), glm::vec2(x + 1, y + 1));
}

const std::vector<glm::vec2> Map::getEmptyTilePositions() const {
  std::vector<glm::vec2> emptyPositions;
  for (int y = 0; y < getHeight(); ++y) {
    for (int x = 0; x < getWidth(); ++x) {
      if (grid[y][x].getType() == MapTileType::EMPTY) {
        emptyPositions.emplace_back(x, y);
      }
    }
  }
  return emptyPositions;
}
