#pragma once

//Opengl
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "glbasimac/glbi_engine.hpp"

using namespace glbasimac;

//External files
#include "managers/sceneManager.hpp"
#include "characters/player.hpp"
#include "characters/phantom.hpp"
#include "map/grid.hpp"


/* Minimal time wanted between two images */
// static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static float aspectRatio = 1.0f;
static const float GL_VIEW_SIZE = 20.; // Vue caméra
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 800;

/* OpenGL Engine */
extern GLBI_Engine myEngine;

struct Game
{
    GLFWwindow* window;  
    Player* player;
    std::vector<std::shared_ptr<Phantom>> phantomsList; // Liste des fantômes
    SceneManager sceneManager {};
    std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> grid;
};

void initGame();

// Getters
Game* getGame();
std::shared_ptr<Scene> getCurrentScene();
Player* getPlayer();
std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT>& getGrid();

// Setters
void lunchVictoryScene();
void lunchLoseScene();
void lunchGameScene();
void lunchHomeScene();