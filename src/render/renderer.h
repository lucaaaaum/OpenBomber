#pragma once

#include "render/sprite.h"
#include <vector>

class Renderer {
private:
  std::vector<Sprite> sprites;

public:
  void render();
};
