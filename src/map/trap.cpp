#include "map/trap.hpp"
#include "map/grid.hpp"
#include "characters/player.hpp"
#include "managers/gameManager.hpp"
#include "managers/text.hpp"

trap createTraps(int id, int positionX, int positionY)
{
    return trap{id, positionX, positionY};
}

std::vector<trap>& traps()
{
    static std::vector<trap> trapList; // Initialized only once

    if (trapList.empty())
    {
        std::srand(std::time(nullptr) + 1000); // rand seed different then item
        for (int i = 0; i < 30; ++i)
        {
            int posX, posY;
            do
            {
                posX = std::rand() % MAP_WIDTH;
                posY = std::rand() % MAP_HEIGHT;
            } while (!isAlive(posX, posY) || (posX == 50 && posY == 50));

            trapList.push_back(createTraps(i, posX, posY));
        }
        displayTraps(trapList); // Debug info
    }

    return trapList;
}

void displayTraps(std::vector<trap> &traps)
{
    std::cout << "traps.size() = " << traps.size() << std::endl;
    for (const auto &oneTrap : traps)
    {
        std::cout << "Trap ID: " << oneTrap.id
                  << ", Position: (" << oneTrap.positionX << ", " << oneTrap.positionY << ")" << std::endl;
    }
}

void playerCollidesWithTrap(std::vector<trap> &traps)
{
    // Player *player = getGame()->player;
    // int playerZone = 1;
    // int playerX = static_cast<int>(player->getPosition().x) + MAP_WIDTH / 2;
    // int playerY = static_cast<int>(player->getPosition().y) + MAP_HEIGHT / 2;

    // for (const auto &oneItem : traps)
    // {
    //     if (!oneItem.collected &&
    //         std::abs(playerX - oneItem.positionX) <= playerZone &&
    //         std::abs(playerY - oneItem.positionY) <= playerZone)
    //     {
    //         glfwGetWindowSize(getGame()->window, &playerX, &playerY);
    //         textDraw("Press 'E' to collect a part of the cane!",
    //                  playerX, playerY - 100, SimpleText::Color::WHITE,
    //                  SimpleText::Alignment::CENTER, SimpleText::SIZE_16, true);
    //     }
    // }
}