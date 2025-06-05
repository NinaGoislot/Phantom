#include "map/obstacle.hpp"
#include "map/grid.hpp"
#include "characters/player.hpp"
#include "managers/gameManager.hpp"
#include "managers/text.hpp"

obstacle createObstacles(int id, int positionX, int positionY)
{
    return obstacle{id, positionX, positionY};
}

std::vector<obstacle>& obstacles()
{
    static std::vector<obstacle> obstList; // Initialized only once

    if (obstList.empty())
    {
        std::srand(std::time(nullptr) + 100); // rand seed different than item or trap
        for (int i = 0; i < 30; ++i)
        {
            int posX, posY;
            do
            {
                posX = std::rand() % MAP_WIDTH;
                posY = std::rand() % MAP_HEIGHT;
            } while (isAlive(posX, posY));

            obstList.push_back(createObstacles(i, posX, posY));
        }
        displayObstacles(obstList); // Debug info
    }

    return obstList;
}

void displayObstacles(std::vector<obstacle> &obstacles)
{
    std::cout << "obstacles.size() = " << obstacles.size() << std::endl;
    for (const auto &oneObst : obstacles)
    {
        std::cout << "Obst ID: " << oneObst.id
                  << ", Position: (" << oneObst.positionX << ", " << oneObst.positionY << ")" << std::endl;
    }
}