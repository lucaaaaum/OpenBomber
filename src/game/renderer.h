#pragma once

class Game;

class Renderer {
public:
  virtual ~Renderer() = default;
  virtual void draw(const Game &game) = 0;
};
