#include "pathfinding.hpp"
#include "managers/gameManager.hpp"
#include "map/grid.hpp"
#include <queue>

bool isInsideGrid(const glm::ivec2 &pos)
{
    return pos.x >= 0 && pos.x < MAP_WIDTH && pos.y >= 0 && pos.y < MAP_HEIGHT;
}

void generateFlowField()
{
    // params
    const glm::ivec2 playerPos = getPlayer()->getPosition();
    std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> &grid = getGrid();
    const int maxDistance = GL_VIEW_SIZE; // distance max pour le calcul du flow field = la taille de la vue
    std::array<glm::ivec2, 4> directions = {glm::ivec2{0, 1}, glm::ivec2{1, 0}, glm::ivec2{0, -1}, glm::ivec2{-1, 0}}; // Directions possibles

    // Initialisation du centre du flow field
    grid[playerPos.y][playerPos.x].direction = {0, 0}; // le joueur est l'objectif à atteindre, donc pas de direction

    // Initialisation de la queue pour BFS
    std::queue<glm::ivec2> cellQueue;
    cellQueue.push(playerPos);

    while (!cellQueue.empty())
    {
        glm::ivec2 currentCell = cellQueue.front();
        cellQueue.pop();

        for (const glm::ivec2 &dir : directions)
        {
            glm::ivec2 neighborCell = currentCell + dir;

            // Vérifier si la cellule voisine est dans les limites de la grille
            if (isInsideGrid(neighborCell) && grid[neighborCell.y][neighborCell.x].walkable)
            {
                if (grid[neighborCell.y][neighborCell.x].direction == glm::ivec2{0, 0})
                { // Si la cellule voisine n'a pas encore de direction (on compare à un vecteur {0;0}, l'initialisation par défaut)
                    // Calculer la distance entre la cellule actuelle et le joueur
                    glm::ivec2 distance = currentCell - playerPos;

                    // Si la distance est inférieure à la distance maximale, mettre à jour la direction
                    if (std::abs(distance.x) < maxDistance && std::abs(distance.y) < maxDistance)
                    {
                        grid[neighborCell.y][neighborCell.x].direction = currentCell - neighborCell;
                        cellQueue.push(neighborCell); 
                    }
                    std::cout << (std::abs(distance.x) < maxDistance && std::abs(distance.y) < maxDistance) << std::endl;
                }
            }
        }
    }
}
