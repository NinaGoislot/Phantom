//Opengl
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include "glbasimac/glbi_texture.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/shaders.hpp"

//External files
#include "controls/controls.hpp"
#include "draw_scene.hpp"

//External libs
#include <vector>
#include <cmath>


using namespace glbasimac;

// to add 
#include "map.hpp"

GLBI_Engine myEngine;
GLBI_Texture textureAtlas;

// OpenGL Shapes
StandardMesh floorTile;
StandardMesh wallTile;
StandardMesh wallTileW;
StandardMesh wallTileE;
StandardMesh wallTileS;
StandardMesh wallTileN;
StandardMesh wallTileSE;
StandardMesh wallTileSW;
StandardMesh wallTileNW;
StandardMesh wallTileNE;
StandardMesh wallTileNEW;
StandardMesh wallTileNWS;
StandardMesh wallTileNES;
StandardMesh wallTileWES;
StandardMesh wallTileNWSE;

bool minusAngleActivated = false;

//to add
void drawOneTile(int& x, int& y, StandardMesh& textureTile)
{
    myEngine.activateTexturing(true);
	textureAtlas.attachTexture();
    myEngine.setFlatColor(1.0,1.0,1.0);

    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(Vector3D(static_cast<float>(x), static_cast<float>(y), 0.0));
        myEngine.updateMvMatrix();
        textureTile.draw();
    myEngine.mvMatrixStack.popMatrix();

    textureAtlas.detachTexture();
	myEngine.activateTexturing(false);
}

//to add
void drawMap()
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addHomothety(0.2);
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
                    drawOneTile(w, h, wallTileW);
                }
                else if (!hasWest && !hasNorth && !hasSouth && hasEast)
                {
                    drawOneTile(w, h, wallTileE);
                }
                else if (!hasWest && !hasNorth && hasEast && hasSouth)
                {
                    drawOneTile(w, h, wallTileSE);
                }
                else if (!hasWest && hasNorth && !hasEast && !hasSouth)
                {
                    drawOneTile(w, h, wallTileN);
                }
                else if (hasWest && hasNorth && !hasEast && !hasSouth)
                {
                    drawOneTile(w, h, wallTileNW);
                }
                else if (!hasWest && hasNorth && hasEast && !hasSouth)
                {
                    drawOneTile(w, h, wallTileNE);
                }
                else if (hasWest && !hasNorth && !hasEast && hasSouth)
                {
                    drawOneTile(w, h, wallTileSW);
                }
                else if (!hasWest && !hasNorth && !hasEast && hasSouth)
                {
                    drawOneTile(w, h, wallTileS);
                }
                else if (hasWest && hasNorth && hasEast && !hasSouth)
                {
                    drawOneTile(w, h, wallTileNEW);
                }
                else if (hasWest && hasNorth && !hasEast && hasSouth)
                {
                    drawOneTile(w, h, wallTileNWS);
                }
                else if (!hasWest && hasNorth && hasEast && hasSouth)
                {
                    drawOneTile(w, h, wallTileNES);
                }
                else if (hasWest && !hasNorth && hasEast && hasSouth)
                {
                    drawOneTile(w, h, wallTileWES);
                }
                else if (hasWest && hasNorth && hasEast && hasSouth)
                {
                    drawOneTile(w, h, wallTileNWSE);
                }
                else
                {
                    drawOneTile(w, h, wallTile);
                }
            }
        }
    }
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.popMatrix();
}

void drawTile(const StandardMesh& textureTile) {
    myEngine.activateTexturing(true);
	textureAtlas.attachTexture();
    myEngine.setFlatColor(1.0,1.0,1.0);

    myEngine.mvMatrixStack.pushMatrix();
        textureTile.draw();
    myEngine.mvMatrixStack.popMatrix();

    textureAtlas.detachTexture();
	myEngine.activateTexturing(false);
}

void initTextures() {
    floorTile = Texturing::createMapTileMesh(0,0);
    floorTile.createVAO();
    wallTile = Texturing::createMapTileMesh(3,0);
    wallTile.createVAO();
    wallTileW = Texturing::createMapTileMesh(4,0);
    wallTileW.createVAO();
    wallTileE = Texturing::createMapTileMesh(3,2);
    wallTileE.createVAO();
    wallTileSE = Texturing::createMapTileMesh(4,2);
    wallTileSE.createVAO();
    wallTileS = Texturing::createMapTileMesh(3,1);
    wallTileS.createVAO();
    wallTileN = Texturing::createMapTileMesh(4,1);
    wallTileN.createVAO();
    wallTileNW = Texturing::createMapTileMesh(5,1);
    wallTileNW.createVAO();
    wallTileNE = Texturing::createMapTileMesh(5,2);
    wallTileNE.createVAO();
    wallTileSW = Texturing::createMapTileMesh(5,0);
    wallTileSW.createVAO();
    wallTileNEW = Texturing::createMapTileMesh(6,2);
    wallTileNEW.createVAO();
    wallTileNWS = Texturing::createMapTileMesh(7,0);
    wallTileNWS.createVAO();
    wallTileWES = Texturing::createMapTileMesh(6,1);
    wallTileWES.createVAO();
    wallTileNES = Texturing::createMapTileMesh(6,0);
    wallTileNES.createVAO();
    wallTileNWSE = Texturing::createMapTileMesh(7,1);
    wallTileNWSE.createVAO();
}

void initScene()
{
    Texturing::initTexture(textureAtlas, "Map", "png");

    // Deal with uv position TODO add like a uv function to generate

    // TODO : Change uv during animation to create animation
    // add animator manager

    initTextures();

    generateMap(10);
    playerSpawner(5);
}

void renderScene(const Game& game)
{
    drawMap();

    game.player->draw(myEngine);
}