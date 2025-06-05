#include "menu.hpp"

std::string playerName = "Phantom";

void displayMenu(int item)
{
    glClearColor(0.f, 0.f, 0.f, 0.2f);
    std::string itemCollected = "Item collected: " + std::to_string(item) + "/5";
    textDraw(playerName, 50, 50, SimpleText::Color::GREEN, SimpleText::Alignment::LEFT, SimpleText::SIZE_16);
    textDraw(itemCollected, 50, 100, SimpleText::Color::WHITE, SimpleText::Alignment::LEFT, SimpleText::SIZE_16);
}