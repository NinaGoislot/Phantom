#pragma once
#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include <iostream>
#include <array>
#include <math.h>
#include "controls/controls.hpp"
#include "characters/player.hpp"
#include "time.hpp"

/* Minimal time wanted between two images */
// static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static float aspectRatio = 1.0f;
static const float GL_VIEW_SIZE = 20.;
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 800;

struct Game
{
    GLFWwindow *window; 
    Player* player;
};

Game initGame();
