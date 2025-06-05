#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <ctime>

struct trap
{
    int id;
    int positionX;
    int positionY;
};


trap createTraps(int id, int positionX, int positionY);

void displayTraps(std::vector<trap> &traps);

std::vector<trap>& traps();

void playerCollidesWithTrap(std::vector<trap> &traps);