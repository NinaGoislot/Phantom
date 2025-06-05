#pragma once 
#include "scene.hpp"
#include <iostream>

struct MenuScene : public Scene
{
    MenuScene()=default;
    void init() override;
    void update() override;
    void draw() override;
    void destroy() override;
};

