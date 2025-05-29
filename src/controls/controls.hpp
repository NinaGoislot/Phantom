#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <unordered_map>

namespace Controls {
    void setupCallbacks(GLFWwindow *window);
    extern std::unordered_map<int, bool> _keysState;
}

