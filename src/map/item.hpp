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

// static std::vector<item> items;

item createItems(int id, int positionX, int positionY, bool collected = false);

void displayItems(std::vector<item> &items);

std::vector<item>& items();

std::vector<item> getItem(std::vector<item> &items);

void playerCloseToItem(std::vector<item> &items);

int countItemsCollected(std::vector<item> &items);