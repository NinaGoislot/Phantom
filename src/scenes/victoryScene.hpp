#pragma once 
#include "scene.hpp"
#include <iostream>

struct VictoryScene : public Scene
{
    VictoryScene()=default;
    void init() override;
    void update() override;
    void draw() override;
    void destroy() override;
};

