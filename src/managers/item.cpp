#include "managers/item.hpp"
#include "map/map.hpp"


item createItems(int id, int positionX, int positionY, bool collected)
{
    return item{id, positionX, positionY, collected};
}

void createItems()
{
    std::srand(std::time({}));
    for (int i{0}; i < 5; i++)
    {
        int posX, posY;

        do
        {
            posX = std::rand() % MAP_WIDTH;
            posY = std::rand() % MAP_HEIGHT;
        } while (isAlive(posX, posY));

        items.push_back(createItems(i, posX, posY, false));
    }
    displayItems();
}

void displayItems()
{
    for (const auto &oneItem : items)
    {
        std::cout << "Item ID: " << oneItem.id
                  << ", Position: (" << oneItem.positionX << ", " << oneItem.positionY << ")"
                  << ", Collected: " << (oneItem.collected ? "Yes" : "No") << std::endl;
    }
}


// int countItemCollecteds();