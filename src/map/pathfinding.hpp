#pragma once

#include <vector>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>


void generateFlowField();
bool isInsideGrid(const glm::ivec2 &pos);
void drawFlowField();
