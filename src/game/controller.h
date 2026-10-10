#pragma once

enum class ControllerAction {
  MOVE_UP,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,
  PLACE_BOMB,
  QUIT
};

class Controller {
public:
  virtual ~Controller() = default;
  virtual void update() = 0;
  virtual bool isDown(ControllerAction action) const = 0;
  virtual bool isPressed(ControllerAction action) const = 0;
};
