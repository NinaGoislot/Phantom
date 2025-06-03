#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <unordered_map>

class Controls
{
public:
    void setKeyState(int key, bool isPressed);
    bool isKeyPressed(int key) const;
    void reset();

private:
    std::unordered_map<int, bool> keyStates;
};

void setupControlsCallbacks(GLFWwindow *window);
void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
