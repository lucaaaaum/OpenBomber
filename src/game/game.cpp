#include "game/game.h"

Game::Game(Controller &controller, Renderer &renderer)
    : controller(controller), renderer(renderer), map(30, 10) {}

void Game::run() {
  while (true) {
    controller.update();
    if (controller.isDown(ControllerAction::QUIT)) {
      break;
    }

    renderer.draw(*this);
  }
}
