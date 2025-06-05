#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <ctime>

struct obstacle
{
    int id;
    int positionX;
    int positionY;
};


obstacle createObstacles(int id, int positionX, int positionY);

void displayObstacles(std::vector<obstacle> &obstacles);

std::vector<obstacle>& obstacles();

void playerCollidesWithObstacle(std::vector<obstacle> &obstacles);

bool isObstacleAt(int x, int y);