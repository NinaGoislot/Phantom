#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <ctime>



struct item
{
    int id;
    int positionX;
    int positionY;
    bool collected;
};

static std::vector<item> items;

item createItems(int id, int positionX, int positionY, bool collected = false);

void createItems();

void displayItems();

int countItemsCollected();