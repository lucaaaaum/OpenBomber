#include "engine/render/renderer.h"

int main() {
  auto renderer = Renderer();
  renderer.init();
  while (true) {
    renderer.render();
  }
}
