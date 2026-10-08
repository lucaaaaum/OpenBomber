#include <vector>

enum MapTileType {
    EMPTY,
    UNBREAKABLE_WALL,
    BREAKABLE_WALL,
    BOMB,
    FIRE
};

class MapTile {
    private:
    MapTileType type;
};

class Map {
    private:
    std::vector<std::vector<MapTile>> grid; 
    public:
    Map(int width, int height) {
        grid = std::vector<std::vector<MapTile>>(height);
        for (int i = 0; i < height; i++)
            grid.push_back(std::vector<MapTile>(width));
    }
};