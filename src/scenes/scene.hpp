#pragma once
#include "glbasimac/glbi_texture.hpp"
#include "tools/mesh.hpp"
#include "controls/controls.hpp"

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void destroy() = 0;

    int BUTTON_SIZE_X {};
    int BUTTON_SIZE_Y {};

    float BUTTON_OFFSET_X {};
    float BUTTON_OFFSET_Y {};

    Controls controls{};
    bool isActive = true;

    void drawBackground(glbasimac::GLBI_Texture &Texture, STP3D::StandardMesh &Tile);
    void drawButton(glbasimac::GLBI_Texture &Texture, STP3D::StandardMesh &Tile, float BUTTON_OFFSET_X, float BUTTON_OFFSET_Y);
};