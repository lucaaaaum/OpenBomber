#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "infra/opengl/gl-renderer.h"

GlRenderer::GlRenderer(GLFWwindow *window) : window(window) {}

void GlRenderer::draw(const Game &game) {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glfwSwapBuffers(window);
}
