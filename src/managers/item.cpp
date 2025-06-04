#include "managers/item.hpp"
#include "map/map.hpp"
#include "characters/player.hpp"
#include "managers/gameManager.hpp"


item createItems(int id, int positionX, int positionY, bool collected)
{
    return item{id, positionX, positionY, collected};
}

std::vector<item> items()
{
    static std::vector<item> itemList; // Initialized only once

    if (itemList.empty()) {
        std::srand(std::time(nullptr));
        for (int i = 0; i < 1; ++i)
        {
            int posX, posY;
            do {
                posX = std::rand() % 5;
                posY = std::rand() % 5;
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

void getItem(std::vector<item> &items) {
    Player* player = getGame()->player;
    for (auto &oneItem : items)
    {
        if (!oneItem.collected && player->getPosition().x == oneItem.positionX && player->getPosition().y == oneItem.positionY)
        {
            oneItem.collected = true;
            std::cout << "Item ID: " << oneItem.id << " collected!" << std::endl;
        }
    }
    std::cout << "No item collected." << std::endl;
}

int count {0};

int countItemsCollected(std::vector<item> &items) {
    for (const auto &oneItem : items)
    {
        if (oneItem.collected)
        {
            count++;
        }
    }
    return count;
}