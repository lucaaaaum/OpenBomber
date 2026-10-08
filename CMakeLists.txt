cmake_minimum_required(VERSION 3.24)
project(openbomber C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
  FIND_PACKAGE_ARGS NAMES glfw3)

FetchContent_Declare(glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.1
  FIND_PACKAGE_ARGS)

FetchContent_MakeAvailable(glfw glm)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(openbomber ${SOURCES} common/glad.c)

target_include_directories(openbomber PRIVATE src include include/glad)
target_link_libraries(openbomber PRIVATE glfw glm::glm OpenGL::GL)