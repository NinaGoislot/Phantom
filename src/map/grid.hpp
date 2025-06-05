#pragma once



//-----------------------------------------------------------------------------------------
//---------------------------------------- INCLUDE ----------------------------------------
//-----------------------------------------------------------------------------------------

#include <iostream>
#include <ctime>
#include <random>
#include <glm/glm.hpp>
#include <array>

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

//-----------------------------------------------------------------------------------------
//---------------------------------------- PARAMS -----------------------------------------
//-----------------------------------------------------------------------------------------

struct Cell {
    glm::ivec2 direction {0, 0};
    bool walkable {false};
    bool visited{false};
};


//-----------------------------------------------------------------------------------------
//--------------------------------------- FUNCTIONS ---------------------------------------
//-----------------------------------------------------------------------------------------

// Generation de la map
std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> generateMap(int generations = 10, int spawnSize = 5);

bool isAlive(int x, int y);
// détruit la case (action de creuser)
void digTile(int x, int y);

// fonction d'affichage de la map
void displayMap();