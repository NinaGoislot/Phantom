#pragma once 
#include "scene.hpp"
#include <iostream>

struct GameScene : public Scene
{
    GameScene()=default;
    void init() override;
    void update() override;
    void draw() override;
    void destroy() override;
};
