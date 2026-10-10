#include "game/map.h"

MapTile::MapTile(MapTileType type) : type(type) {}

MapTileType MapTile::getType() const { return type; }

Map::Map(int width, int height) : grid(height, std::vector<MapTile>(width)) {}

MapTile *Map::getTile(int x, int y) {
  int height = grid.size();
  int width = grid[0].size();
  if (x < 0 || y < 0 || x >= width || y >= height) {
    return nullptr;
  }
  return &grid[y][x];
}
