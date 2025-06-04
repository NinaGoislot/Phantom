#include "pathfinding.hpp"
#include "managers/gameManager.hpp"
#include "map/grid.hpp"

void generateFlowField(){
    //params
    const glm::ivec2 playerPos = getPlayer()->getPosition();
    std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT>& grid = getGrid();
    const int maxDistance = GL_VIEW_SIZE; // distance max pour le calcul du flow field = la taille de la vue

    grid[playerPos.y][playerPos.x].direction = {0, 0}; // le joueur est l'objectif à atteindre, donc pas de direction



}