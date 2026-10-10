#include <glad/glad.h>

#include "game/game.h"
#include "infra/opengl/gl-renderer.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using std::string;

const char *vertexShader = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
uniform mat4 projection;
uniform mat4 model;
void main() {
    gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
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

GlRenderer::GlRenderer(GLFWwindow *window)
    : window(window), playerSprite("assets/player.png") {
  tileSprites = {
      {MapTileType::EMPTY, Sprite("assets/empty-tile.png")},
      {MapTileType::UNBREAKABLE_WALL, Sprite("assets/unbreakable-wall.png")},
      {MapTileType::BREAKABLE_WALL, Sprite("assets/breakable-wall.png")},
      {MapTileType::BOMB, Sprite("assets/bomb.png")},
      {MapTileType::FIRE, Sprite("assets/fire.png")},
      {MapTileType::HAS_PLAYER, Sprite("assets/empty-tile.png")}};
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

  loadSprites();
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

  loadSprites();
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

unsigned int loadTexture(Sprite &sprite);

void GlRenderer::loadSprites() {
  for (auto &[type, sprite] : tileSprites) {
    unsigned int textureId = loadTexture(sprite);
  }
  unsigned int playerTextureId = loadTexture(playerSprite);
}

unsigned int loadTexture(Sprite &sprite) {
  int width, height, channels;
  unsigned char *data =
      stbi_load(sprite.getSourcePath(), &width, &height, &channels, 4);
  if (data == nullptr) {
    throw std::runtime_error(std::string("Failed to load texture ") +
                             sprite.getSourcePath() + ": " +
                             stbi_failure_reason());
  }

  unsigned int textureId;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);
  sprite.setTextureId(textureId);
  sprite.setSize(width, height);

  return textureId;
}

void GlRenderer::draw(const Game &game) {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shaderProgram);
  auto projection = glm::ortho(0.0f, 30.0f, 10.0f, 0.0f, -1.0f, 1.0f);
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1,
                     GL_FALSE, glm::value_ptr(projection));

  glBindVertexArray(vao);

  drawMap(game.getMap());
  drawPlayers(game.getPlayers());

  glfwSwapBuffers(window);
}

void GlRenderer::drawMap(const Map &map) {
  int width = map.getWidth();
  int height = map.getHeight();

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      auto tile = map.getTile(x, y);
      if (!tile) {
        continue;
      }

      glm::vec4 color;
      switch (tile->getType()) {
      case MapTileType::EMPTY:
        color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        break;
      case MapTileType::UNBREAKABLE_WALL:
        color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
        break;
      case MapTileType::BREAKABLE_WALL:
        color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        break;
      case MapTileType::BOMB:
        color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        break;
      case MapTileType::FIRE:
        color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        break;
      case MapTileType::HAS_PLAYER:
        color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        break;
      }

      glUniform4fv(glGetUniformLocation(shaderProgram, "color"), 1,
                   glm::value_ptr(color));
      auto model = glm::translate(
          glm::mat4(1.0f),
          glm::vec3(static_cast<float>(x), static_cast<float>(y), 0.0f));
      glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1,
                         GL_FALSE, glm::value_ptr(model));
      glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
  }
}

void GlRenderer::drawPlayers(const std::vector<Player> &players) {
  glUniform4f(glGetUniformLocation(shaderProgram, "color"), 1.0f, 0.5f, 0.0f,
              1.0f);
  for (const auto &player : players) {
    auto playerPosition = player.getPosition();
    auto model = glm::translate(
        glm::mat4(1.0f), glm::vec3(playerPosition.x, playerPosition.y, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1,
                       GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  }
}

GlRenderer::~GlRenderer() {
  for (auto &[type, sprite] : tileSprites) {
    auto textureId = sprite.getTextureId();
    glDeleteTextures(1, &textureId);
  }
  auto playerTextureId = playerSprite.getTextureId();
  glDeleteTextures(1, &playerTextureId);

  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(shaderProgram);
}
