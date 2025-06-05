#include "map/item.hpp"
#include "map/grid.hpp"
#include "characters/player.hpp"
#include "managers/gameManager.hpp"
#include "managers/text.hpp"

item createItems(int id, int positionX, int positionY, bool collected)
{
    return item{id, positionX, positionY, collected};
}

void checkIfVictory(std::vector<item> &items)
{
    const int count = countItemsCollected(items);
    if (count >= NB_ITEM_TO_FIND)
    {
        lunchVictoryScene();
    }
} 


std::vector<item>& items()
{
    static std::vector<item> itemList; // Initialized only once

    if (itemList.empty())
    {
        std::srand(std::time(nullptr));
        for (int i = 0; i < NB_ITEM_TO_GENERATE; ++i)
        {
            int posX, posY;
            do
            {
                posX = std::rand() % MAP_WIDTH;
                posY = std::rand() % MAP_HEIGHT;
            } while (!isAlive(posX, posY));

            itemList.push_back(createItems(i, posX, posY, false));
        }
        displayItems(itemList); // Debug info
    }

    return itemList;
}

void displayItems(std::vector<item> &items)
{
    std::cout << "items.size() = " << items.size() << std::endl;
    for (const auto &oneItem : items)
    {
        std::cout << "Item ID: " << oneItem.id
                  << ", Position: (" << oneItem.positionX << ", " << oneItem.positionY << ")"
                  << ", Collected: " << (oneItem.collected ? "Yes" : "No") << std::endl;
    }
}



void getItem(std::vector<item> &items)
{
    Player *player = getGame()->player;
    int playerZone = 1;
    int playerX = static_cast<int>(player->getPosition().x) + MAP_WIDTH / 2;
    int playerY = static_cast<int>(player->getPosition().y) + MAP_HEIGHT / 2;
    for (auto &oneItem : items)
    {
        if (!oneItem.collected)
        {
            if (!oneItem.collected &&
                std::abs(playerX - oneItem.positionX) <= playerZone &&
                std::abs(playerY - oneItem.positionY) <= playerZone)
            {
                oneItem.collected = true;
                std::cout << "Item " << oneItem.id << " collected!" << std::endl;
            }
        }
    }
    checkIfVictory(items);
}

void playerCloseToItem(std::vector<item> &items)
{
    Player *player = getGame()->player;
    int playerZone = 1;
    int playerX = static_cast<int>(player->getPosition().x) + MAP_WIDTH / 2;
    int playerY = static_cast<int>(player->getPosition().y) + MAP_HEIGHT / 2;

    for (const auto &oneItem : items)
    {
        if (!oneItem.collected &&
            std::abs(playerX - oneItem.positionX) <= playerZone &&
            std::abs(playerY - oneItem.positionY) <= playerZone)
        {
            glfwGetWindowSize(getGame()->window, &playerX, &playerY);
            textDraw("Press 'E' to collect a part of the cane!",
                     playerX, playerY - 100, SimpleText::Color::WHITE,
                     SimpleText::Alignment::CENTER, SimpleText::SIZE_16, true);
        }
    }
}


int countItemsCollected(std::vector<item> &items)
{
    int count{0};
    for (const auto &oneItem : items)
    {
        if (oneItem.collected)
        {
            count++;
        }
    }
    return count;
}