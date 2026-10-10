#pragma once

#include <vector>

enum class MapTileType {
  EMPTY,
  UNBREAKABLE_WALL,
  BREAKABLE_WALL,
  BOMB,
  FIRE,
  HAS_PLAYER
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
};
