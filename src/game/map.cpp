#include "game/map.h"

MapTile::MapTile(MapTileType type) : type(type) {}

MapTileType MapTile::getType() const { return type; }

Map::Map(int width, int height)
    : grid(height, std::vector<MapTile>(width)) {}
