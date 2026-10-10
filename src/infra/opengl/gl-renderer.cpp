#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <stdexcept>

#include "infra/opengl/gl-renderer.h"

using std::string;

const char *vertexShader = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

const char *fragmentShader = R"(
#version 330 core
uniform vec4 color;
out vec4 fragColor;
void main() {
    fragColor = color;
}
)";

GlRenderer::GlRenderer(GLFWwindow *window) : window(window) {
  createShaderProgram();

  float vertices[] = {
      0, 0, // v0
      1, 0, // v1
      1, 1, // v2
      0, 1, // v3
  };

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
}

unsigned int createShader(int shaderType, const char *shaderSource);

void GlRenderer::createShaderProgram() {
  auto vertexShaderId = createShader(GL_VERTEX_SHADER, vertexShader);
  auto fragmentShaderId = createShader(GL_FRAGMENT_SHADER, fragmentShader);

  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShaderId);
  glAttachShader(shaderProgram, fragmentShaderId);
  glLinkProgram(shaderProgram);

  int success;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    throw std::runtime_error(std::string("Shader linking failed: ") + infoLog);
  }

  glDeleteShader(vertexShaderId);
  glDeleteShader(fragmentShaderId);
}

unsigned int createShader(int shaderType, const char *shaderSource) {
  auto shaderId = glCreateShader(shaderType);
  glShaderSource(shaderId, 1, &shaderSource, nullptr);
  glCompileShader(shaderId);

  int success;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
    throw std::runtime_error(string("Shader compilation failed: ") + infoLog);
  }

  return shaderId;
}

void GlRenderer::draw(const Game &game) {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shaderProgram);
  glUniform4f(glGetUniformLocation(shaderProgram, "color"), 1.0f, 0.5f, 0.0f,
              1.0f);
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  glfwSwapBuffers(window);
}

GlRenderer::~GlRenderer() {
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(shaderProgram);
}
