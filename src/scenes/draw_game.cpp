//Opengl
#include "glad/glad.h" // DOIT être le premier include lié à OpenGL
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include "glbasimac/glbi_texture.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/shaders.hpp"
#include "tools/basic_mesh.hpp"
#include "glbasimac/glbi_engine.hpp"
#include "map.hpp"
using namespace glbasimac;

//External files
#include "controls/controls.hpp"
#include "scenes/draw_game.hpp"

//External libs
#include <vector>
#include <cmath>

GLBI_Engine myEngine;
GLBI_Texture textureAtlas;

// OpenGL Shapes
StandardMesh floorTile;
StandardMesh wallTile;

void drawOneTile(int& x, int& y, StandardMesh& textureTile)
{
    myEngine.setFlatColor(1.0,1.0,1.0);

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
    myEngine.mvMatrixStack.addHomothety(1);
    myEngine.updateMvMatrix();
        myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(Vector3D(-MAP_WIDTH/2, -MAP_HEIGHT/2, 0.0));
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

                if (hasWest && !hasEast && !hasNorth && !hasSouth)
                {
                    // W
                    Texturing::updateUVs(wallTile, 0,4, 16, 16, 128, 128);
                }
                else if (!hasWest && !hasNorth && !hasSouth && hasEast)
                {
                    // E
                    Texturing::updateUVs(wallTile, 2,3, 16, 16, 128, 128);
                }
                else if (!hasWest && !hasNorth && hasEast && hasSouth)
                {
                    // SE
                    Texturing::updateUVs(wallTile, 2,4, 16, 16, 128, 128);
                }
                else if (!hasWest && hasNorth && !hasEast && !hasSouth)
                {
                    // N
                    Texturing::updateUVs(wallTile, 1,4, 16, 16, 128, 128);
                }
                else if (hasWest && hasNorth && !hasEast && !hasSouth)
                {
                    // WN
                    Texturing::updateUVs(wallTile, 1,5, 16, 16, 128, 128);
                }
                else if (!hasWest && hasNorth && hasEast && !hasSouth)
                {
                    // NE
                    Texturing::updateUVs(wallTile, 2,5, 16, 16, 128, 128);
                }
                else if (hasWest && !hasNorth && !hasEast && hasSouth)
                {
                    // SW
                    Texturing::updateUVs(wallTile, 0,5, 16, 16, 128, 128);
                }
                else if (!hasWest && !hasNorth && !hasEast && hasSouth)
                {
                    // S
                    Texturing::updateUVs(wallTile, 1,3, 16, 16, 128, 128);
                }
                else if (hasWest && hasNorth && hasEast && !hasSouth)
                {
                    // NEW
                    Texturing::updateUVs(wallTile, 2,6, 16, 16, 128, 128);
                }
                else if (hasWest && hasNorth && !hasEast && hasSouth)
                {
                    // NSW
                    Texturing::updateUVs(wallTile, 0,7, 16, 16, 128, 128);
                }
                else if (!hasWest && hasNorth && hasEast && hasSouth)
                {
                    // NES
                    Texturing::updateUVs(wallTile, 0,6, 16, 16, 128, 128);
                }
                else if (hasWest && !hasNorth && hasEast && hasSouth)
                {
                    // WES
                    Texturing::updateUVs(wallTile, 1,6, 16, 16, 128, 128);
                }
                else if (hasWest && hasNorth && hasEast && hasSouth)
                {
                    Texturing::updateUVs(wallTile, 1,7, 16, 16, 128, 128);
                }
                else if (!hasWest && hasNorth && !hasEast && hasSouth)
                {
                    // NS
                    Texturing::updateUVs(wallTile, 3,7, 16, 16, 128, 128);
                }
                else if (hasWest && !hasNorth && hasEast && !hasSouth)
                {
                    // WE
                    Texturing::updateUVs(wallTile, 3,6, 16, 16, 128, 128);
                }
                else
                {
                    // Surrounded/default
                    Texturing::updateUVs(wallTile, 0,3, 16, 16, 128, 128);
                }
                drawOneTile(w, h, wallTile);
            }
        }
    }
        myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.activateTexturing(false);
	textureAtlas.detachTexture();
}

void initTextures() {
    floorTile = Texturing::createMapTileMesh(0,0);
    floorTile.createVAO();
    wallTile = Texturing::createMapTileMesh(3,0);
    wallTile.createVAO();
}

void DrawGame::init()
{
    Texturing::initTexture(textureAtlas, "Map", "png");

    initTextures();

    generateMap(10);
    playerSpawner(5);
}

void DrawGame::render(const Game& game)
{
    drawMap();

    game.player->draw(myEngine);
}