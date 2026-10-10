#pragma once

#include "infra/opengl/gl-controller.h"
#include "infra/opengl/gl-renderer.h"
#include <glm/glm.hpp>
#include <memory>

struct GLFWwindow;

class GlfwPlatform {
private:
  GLFWwindow *window = nullptr;
  std::unique_ptr<GlController> controller;
  std::unique_ptr<GlRenderer> renderer;

public:
  GlfwPlatform(glm::ivec2 size, const char *title);
  ~GlfwPlatform();
  GlfwPlatform(const GlfwPlatform &) = delete;
  GlfwPlatform &operator=(const GlfwPlatform &) = delete;
  Controller &getController();
  Renderer &getRenderer();
};
