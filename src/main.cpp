#include "render/sprite.h"
#include "render/renderer.cpp"

#include <iostream>

int main() {
    auto renderer = Renderer();
    while (true) {
        renderer.render();
    }
}