#include "render/renderer.h"

int main() {
  auto renderer = Renderer();
  while (true) {
    renderer.render();
  }
}
