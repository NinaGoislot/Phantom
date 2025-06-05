#pragma once

#include <vector>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include "managers/gameManager.hpp"


void generateFlowField();
bool isInsideGrid(const glm::ivec2 &pos);
void drawFlowField();

const int MAX_DISTANCE = GL_VIEW_SIZE / 2;
