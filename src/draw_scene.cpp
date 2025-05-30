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

bool minusAngleActivated = false;

//to add
void drawOneTile(int& x, int& y, const StandardMesh& textureTile)
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
                drawOneTile(w, h, wallTile);
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

void initScene()
{
    Texturing::initTexture(textureAtlas, "Map", "png");

    // Deal with uv position TODO add like a uv function to generate

    // TODO : Change uv during animation to create animation
    // add animator manager

    floorTile = Texturing::createMapTileMesh(0, 2);
    floorTile.createVAO();
    wallTile = Texturing::createMapTileMesh(0, 3);
    wallTile.createVAO();

    generateMap(10);
    playerSpawner(5);
}

void renderScene(const Game& game)
{
    drawMap();

    game.player->draw(myEngine);
}