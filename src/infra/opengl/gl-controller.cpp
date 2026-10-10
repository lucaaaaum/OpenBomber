#include <GLFW/glfw3.h>

#include "infra/opengl/gl-controller.h"
#include <vector>

static const std::map<ControllerAction, std::vector<int>> KEY_BINDINGS = {
    {ControllerAction::MOVE_UP, {GLFW_KEY_W, GLFW_KEY_UP}},
    {ControllerAction::MOVE_DOWN, {GLFW_KEY_S, GLFW_KEY_DOWN}},
    {ControllerAction::MOVE_LEFT, {GLFW_KEY_A, GLFW_KEY_LEFT}},
    {ControllerAction::MOVE_RIGHT, {GLFW_KEY_D, GLFW_KEY_RIGHT}},
    {ControllerAction::PLACE_BOMB, {GLFW_KEY_SPACE}},
    {ControllerAction::QUIT, {GLFW_KEY_ESCAPE}},
};

static bool get(const std::map<ControllerAction, bool> &actions,
                ControllerAction action) {
  auto it = actions.find(action);
  return it != actions.end() && it->second;
}

GlController::GlController(GLFWwindow *window) : window(window) {}

void GlController::update() {
  previous = current;
  current.clear();

  glfwPollEvents();

  for (const auto &[action, keys] : KEY_BINDINGS) {
    for (int key : keys) {
      if (glfwGetKey(window, key) == GLFW_PRESS) {
        current[action] = true;
      }
    }
  }

  if (glfwWindowShouldClose(window)) {
    current[ControllerAction::QUIT] = true;
  }
}

bool GlController::isDown(ControllerAction action) const {
  return get(current, action);
}

bool GlController::isPressed(ControllerAction action) const {
  return get(current, action) && !get(previous, action);
}
