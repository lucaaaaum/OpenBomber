#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "engine/render/renderer.h"
#include <iostream>

int Renderer::getWindowWidth() const { return windowSize.x; }

int Renderer::getWindowHeight() const { return windowSize.y; }

void Renderer::init() {
  glfwInit();
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window = glfwCreateWindow(800, 600, "OpenBomber", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
}

void Renderer::render() {
  if (!window) {
    std::cerr << "Window not initialized" << std::endl;
    return;
  }

  if (glfwWindowShouldClose(window)) {
    glfwTerminate();
    return;
  }

  glfwPollEvents();

  glClear(GL_COLOR_BUFFER_BIT);

  glfwSwapBuffers(window);
}
