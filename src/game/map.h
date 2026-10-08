#pragma once

#include <vector>

enum class MapTileType { EMPTY, UNBREAKABLE_WALL, BREAKABLE_WALL, BOMB, FIRE };

class MapTile {
private:
  MapTileType type;

public:
  MapTile(MapTileType type = MapTileType::EMPTY);
  MapTileType getType() const;
};

class Map {
private:
  std::vector<std::vector<MapTile>> grid;

public:
  Map(int width, int height);
};
