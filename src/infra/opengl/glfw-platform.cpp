#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "infra/opengl/glfw-platform.h"
#include <stdexcept>

GlfwPlatform::GlfwPlatform(glm::ivec2 size, const char *title) {
  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialize GLFW");
  }

  window = glfwCreateWindow(size.x, size.y, title, nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwDestroyWindow(window);
    glfwTerminate();
    throw std::runtime_error("Failed to initialize GLAD");
  }

  controller = std::make_unique<GlController>(window);
  renderer = std::make_unique<GlRenderer>(window);
}

GlfwPlatform::~GlfwPlatform() {
  renderer.reset();
  controller.reset();

  glfwDestroyWindow(window);
  glfwTerminate();
}

Controller &GlfwPlatform::getController() { return *controller; }

Renderer &GlfwPlatform::getRenderer() { return *renderer; }
