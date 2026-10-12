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
