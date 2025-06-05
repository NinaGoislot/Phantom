#pragma once 
#include "scene.hpp"
#include <iostream>

struct EndScene : public Scene
{
    EndScene()=default;
    void init() override;
    void update() override;
    void draw() override;
    void destroy() override;
};

