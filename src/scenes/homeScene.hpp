#pragma once 
#include "scene.hpp"
#include "glbasimac/glbi_texture.hpp"
#include <iostream>
#include "tools/mesh.hpp"

void drawOneImage(int &x, int &y, StandardMesh &textureTile);

struct HomeScene : public Scene
{
    HomeScene()=default;
    void init() override;
    void update() override;
    void draw() override;
    void destroy() override;
};