#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <ctime>

struct floorT
{
    int id;
    int positionX;
    int positionY;
};


floorT createFloors(int id, int positionX, int positionY);

std::vector<floorT>& floors();

void displayFloors(const std::vector<floorT>& floors);

const std::vector<std::vector<int>>& getTileIdMap();