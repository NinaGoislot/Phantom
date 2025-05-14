#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include "game.hpp"

namespace Controls {
    void setupCallbacks(GLFWwindow *window);
}

