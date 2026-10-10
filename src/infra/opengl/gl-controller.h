#pragma once

#include "game/controller.h"
#include <map>

struct GLFWwindow;

class GlController : public Controller {
private:
  GLFWwindow *window;
  std::map<ControllerAction, bool> current;
  std::map<ControllerAction, bool> previous;

public:
  explicit GlController(GLFWwindow *window);
  void update() override;
  bool isDown(ControllerAction action) const override;
  bool isPressed(ControllerAction action) const override;
};
