#include "game/game.h"
#include "infra/opengl/glfw-platform.h"
#include <exception>
#include <iostream>

int main() {
  std::cout << "Starting OpenBomber..." << std::endl;
  try {
    GlfwPlatform platform({800, 600}, "OpenBomber v0.1.0");
    Game game(platform.getController(), platform.getRenderer());
    game.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  std::cout << "Exiting OpenBomber..." << std::endl;
  return 0;
}
