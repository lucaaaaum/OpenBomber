#include "game/map.h"

MapTile::MapTile(MapTileType type) : type(type) {}

MapTileType MapTile::getType() const { return type; }

Map::Map(int width, int height) : grid(height, std::vector<MapTile>(width)) {}

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
