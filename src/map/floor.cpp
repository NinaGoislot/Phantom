#include "map/floor.hpp"
#include "map/grid.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

static std::vector<floorT> floorList;
static std::vector<std::vector<int>> tileIdMap;

floorT createFloors(int id, int positionX, int positionY)
{
    return floorT{id, positionX, positionY};
}

std::vector<floorT>& floors()
{
    if (!floorList.empty())
        return floorList;

    tileIdMap.resize(MAP_WIDTH, std::vector<int>(MAP_HEIGHT, 0));

    for (int x = 0; x < MAP_WIDTH; ++x)
    {
        for (int y = 0; y < MAP_HEIGHT; ++y)
        {
            int tileId = std::rand() % 9; // Random ID from 0 to 8 (3x3 atlas)
            tileIdMap[x][y] = tileId;
            floorList.emplace_back(createFloors(tileId, x, y));
        }
    }

    // displayFloors(floorList);
    return floorList;
}

const std::vector<std::vector<int>>& getTileIdMap()
{
    if (tileIdMap.empty())
        floors(); // ensure it's initialized
    return tileIdMap;
}

void displayFloors(const std::vector<floorT>& floors)
{
    std::cout << "floors.size() = " << floors.size() << std::endl;
    for (const auto& f : floors)
    {
        std::cout << "Floor ID: " << f.id
                  << ", Position: (" << f.positionX << ", " << f.positionY << ")\n";
    }
}
