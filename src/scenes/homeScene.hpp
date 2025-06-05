#pragma once 
#include "scene.hpp"
#include <iostream>

struct HomeScene : public Scene
{
    HomeScene()=default;
    void init() override;
    void update() override;
    void draw() override;
    void destroy() override;
};