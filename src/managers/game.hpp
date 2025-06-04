#pragma once

//Opengl
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "glbasimac/glbi_engine.hpp"

using namespace glbasimac;

//External files
#include "managers/sceneManager.hpp"
#include "characters/player.hpp"
#include "map.hpp"

/* Minimal time wanted between two images */
// static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static float aspectRatio = 1.0f;
static const float GL_VIEW_SIZE = 20.;
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 800;

/* OpenGL Engine */
extern GLBI_Engine myEngine;

struct Game
{
    GLFWwindow* window;  
    Player* player;
    SceneManager sceneManager {};
};

Game initGame();
Game* getGame();
