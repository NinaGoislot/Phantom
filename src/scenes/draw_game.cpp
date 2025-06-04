//Opengl
#include "glad/glad.h"
#define GLFW_INCLUDE_NONE // DOIT être le premier include lié à OpenGL
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include "glbasimac/glbi_texture.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/shaders.hpp"
#include "tools/basic_mesh.hpp"
#include "glbasimac/glbi_engine.hpp"
using namespace glbasimac;

// External files
#include "controls/controls.hpp"
#include "scenes/draw_game.hpp"
#include "map/map.hpp"
#include "managers/item.hpp"
#include "map/map.hpp"

// External libs
#include <vector>
#include <cmath>

// textures
GLBI_Engine myEngine;
GLBI_Texture textureAtlas;

// OpenGL Shapes
StandardMesh floorTile;
StandardMesh wallTile;

int computeBitmask(bool north, bool east, bool south, bool west)
{
    return (north ? 8 : 0) + (east ? 4 : 0) + (south ? 2 : 0) + (west ? 1 : 0);
}

std::pair<int, int> bitmaskUVs[16] = {
    {0, 3}, // plain terrain/default
    {0, 4}, // W
    {1, 3}, // S
    {0, 5}, // SW
    {2, 3}, // E
    {3, 6}, // WE
    {2, 4}, // SE
    {1, 6}, // WES
    {1, 4}, // N
    {1, 5}, // NW
    {3, 7}, // NS
    {0, 7}, // NSW
    {2, 5}, // NE
    {2, 6}, // NEW
    {0, 6}, // NES
    {1, 7}  // Surrounded
};

void drawOneTile(int &x, int &y, StandardMesh &textureTile)
{
    myEngine.setFlatColor(1.0, 1.0, 1.0);

    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(Vector3D(static_cast<float>(x), static_cast<float>(y), 0.0));
        myEngine.updateMvMatrix();
        textureTile.draw();
    myEngine.mvMatrixStack.popMatrix();
}

void drawMap()
{
    myEngine.activateTexturing(true);
    textureAtlas.attachTexture();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.updateMvMatrix();
        myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation(Vector3D(-MAP_WIDTH / 2, -MAP_HEIGHT / 2, 0.0));
            myEngine.updateMvMatrix();
            for (int h{0}; h < MAP_WIDTH; h++)
                {
            for (int w{0}; w < MAP_HEIGHT; w++)
                {
                if (isAlive(w, h))
                {
                    drawOneTile(w, h, floorTile);
                }
                else
                {
                    bool hasWest = isAlive(w - 1, h);
                    bool hasEast = isAlive(w + 1, h);
                    bool hasNorth = isAlive(w, h + 1);
                    bool hasSouth = isAlive(w, h - 1);

                    int bitmask = computeBitmask(hasNorth, hasEast, hasSouth, hasWest); // we calculate the bistmask id of each walltile based on their neighbours                
                    auto [col, row] = bitmaskUVs[bitmask]; // we retrieve the uv of the texture we wanna apply

                    Texturing::updateUVs(wallTile, col, row, 16, 16, 128, 128);
                    drawOneTile(w, h, wallTile);
                }
            }
        }
        myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.activateTexturing(false);
    textureAtlas.detachTexture();
}

void initTextures()
{
    floorTile = Texturing::createMapTileMesh(0, 0);
    floorTile.createVAO();
    wallTile = Texturing::createMapTileMesh(3, 0);
    wallTile.createVAO();
}

void DrawGame::init()
{
    Texturing::initTexture(textureAtlas, "Map", "png");

    initTextures();

    generateMap(10);
    playerSpawner(5);
}

void DrawGame::render(const Game &game)
{
    // switch to opengl shaders
    myEngine.switchToFlatShading();


    drawMap();

    game.player->draw(myEngine);
}


//voilà comment j'ai appelé mes fonctions tah l'époque

// void drawOneTile(int &x, int &y, float color)
// {
//     myEngine.mvMatrixStack.pushMatrix();
//     myEngine.mvMatrixStack.addTranslation(Vector3D(static_cast<float>(x), static_cast<float>(y), 0.0));
//     myEngine.updateMvMatrix();
//     myEngine.setFlatColor(color, color, color);
//     carre.drawShape();
//     myEngine.mvMatrixStack.popMatrix();
// }

// void drawMap()
// {
//     myEngine.mvMatrixStack.pushMatrix();
//     myEngine.mvMatrixStack.addHomothety(0.2);
//     myEngine.updateMvMatrix();
//     carre.drawShape();
//     myEngine.mvMatrixStack.pushMatrix();
//     myEngine.mvMatrixStack.addTranslation(Vector3D(-MAP_WIDTH / 2, -MAP_HEIGHT / 2, 0.0));
//     myEngine.updateMvMatrix();
//     for (int h{0}; h < MAP_WIDTH; h++)
//     {
//         for (int w{0}; w < MAP_HEIGHT; w++)
//         {
//             if (isAlive(w, h))
//             {
//                 drawOneTile(w, h, 1.0);
//             }
//             else
//             {
//                 drawOneTile(w, h, 0.0);
//             }
//         }
//     }
//     myEngine.mvMatrixStack.popMatrix();
//     myEngine.mvMatrixStack.popMatrix();
// }

// void initScene()
// {
//     textInit();

//     // to add
//     generateMap(10);
//     playerSpawner(5);

//     std::vector<float> originCoord{1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0}; // manually put coord here to match the first arm not ideal
//     carre.initShape(originCoord);
//     carre.changeNature(GL_TRIANGLE_FAN);
// }

// void renderScene()
// {
//     myEngine.switchToFlatShading();
//     drawMap();
//     displayMenu(0); // Display the menu with item 0
//     // textDraw("Lorem ipsum", width, height, SimpleText::CENTER, SimpleText::SIZE_16);
// }