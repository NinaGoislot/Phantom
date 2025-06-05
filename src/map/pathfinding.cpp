#include "pathfinding.hpp"
#include "managers/gameManager.hpp"
#include "map/grid.hpp"
#include <queue>

const int MAX_DISTANCE = GL_VIEW_SIZE / 2;

bool isInsideGrid(const glm::ivec2 &pos)
{
    return pos.x >= 0 && pos.x < MAP_WIDTH && pos.y >= 0 && pos.y < MAP_HEIGHT;
}

void generateFlowField()
{
    // params
    glm::vec2 rawPos = getPlayer()->getPosition();
    rawPos.x = MAP_WIDTH / 2;  // Conversion cordonnées joueur -> coordonnées grille
    rawPos.y = MAP_HEIGHT / 2; // Conversion cordonnées joueur -> coordonnées grille
    glm::ivec2 playerPos = glm::ivec2(glm::round(rawPos));

    std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> &grid = getGrid();
    // distance max pour le calcul du flow field = la taille de la vue
    std::array<glm::ivec2, 4> directions = {glm::ivec2{0, 1}, glm::ivec2{1, 0}, glm::ivec2{0, -1}, glm::ivec2{-1, 0}}; // Directions possibles

    // Initialisation du centre du flow field
    grid[playerPos.y][playerPos.x].direction = {0, 0}; // le joueur est l'objectif à atteindre, donc pas de direction

    // Initialisation de la queue pour BFS
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            grid[y][x].direction = {0, 0};
            grid[y][x].visited = false;
            grid[y][x].distance = MAX_DISTANCE; // Initialiser la distance à la distance maximale
        }
    }

    grid[playerPos.y][playerPos.x].visited = true;
    grid[playerPos.y][playerPos.x].distance = 0;
    std::queue<glm::ivec2> cellQueue;
    cellQueue.push(playerPos);

    while (!cellQueue.empty())
    {
        glm::ivec2 currentCell = cellQueue.front();
        cellQueue.pop();

        int current_distance = grid[currentCell.y][currentCell.x].distance;

        for (const glm::ivec2 &dir : directions)
        {
            glm::ivec2 neighborCell = currentCell + dir;

            // Vérifier si la cellule voisine est dans les limites de la grille
            if (isInsideGrid(neighborCell) && grid[neighborCell.y][neighborCell.x].walkable)
            {
                if (!grid[neighborCell.y][neighborCell.x].visited)
                { // Si la cellule voisine n'a pas encore de direction (on compare à un vecteur {0;0}, l'initialisation par défaut)
                    // Calculer la distance entre la cellule actuelle et le joueur
                    grid[neighborCell.y][neighborCell.x].visited = true;
                    grid[neighborCell.y][neighborCell.x].distance = current_distance + 1;
                    grid[neighborCell.y][neighborCell.x].direction = currentCell - neighborCell;
                    cellQueue.push(neighborCell);
                }
            }
        }
    }
}

void drawFlowField()
{
    auto &grid = getGrid();

    for (int y = MAP_HEIGHT - 1; y >= 0; --y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            glm::ivec2 dir = grid[y][x].direction;
            char c = '.';
            if (dir == glm::ivec2(1, 0))
                c = '>';
            else if (dir == glm::ivec2(-1, 0))
                c = '<';
            else if (dir == glm::ivec2(0, 1))
                c = '^';
            else if (dir == glm::ivec2(0, -1))
                c = 'v';
            else if (dir == glm::ivec2(0, 0))
                c = 'O'; // le joueur
            else
            {
                c = '?';
            }
            std::cout << c << ' ';
        }
        std::cout << '\n';
    }
}