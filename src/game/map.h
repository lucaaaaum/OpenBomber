#pragma once

#include "game/hitbox.h"
#include <vector>

enum class MapTileType {
  EMPTY,
  UNBREAKABLE_WALL,
  BREAKABLE_WALL,
};

class MapTile {
private:
  MapTileType type;

public:
  MapTile(MapTileType type = MapTileType::EMPTY);
  MapTileType getType() const;
  void setType(MapTileType newType) { type = newType; }
};

class Map {
private:
  std::vector<std::vector<MapTile>> grid;

public:
  Map(int width, int height);
  MapTile *getTile(int x, int y);
  const MapTile *getTile(int x, int y) const;
  int getWidth() const;
  int getHeight() const;
  Hitbox getTileHitbox(int x, int y) const;
  const std::vector<glm::vec2> getEmptyTilePositions() const;
};
