#include "draw_scene.hpp"
#include "GLFW/glfw3.h"
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <cmath>
#include "glbasimac/glbi_texture.hpp"
#include "tools/shaders.hpp"

using namespace glbasimac;

GLBI_Engine myEngine;
GLBI_Texture textureAtlas;

// OpenGL Shapes
// GLBI_Convex_2D_Shape carre;
StandardMesh square;
StandardMesh square2;

bool minusAngleActivated = false;

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
    Texturing::initTexture(textureAtlas);

    // Deal with uv position TODO add like a uv function to generate

    // TODO : Change uv during animation to create animation
    // add animator manager

    square = Texturing::createAutoTiledMesh(0.5f);
    square.createVAO();
    square2 = Texturing::createAutoTiledMesh(1.0f);
    square2.createVAO();
}

void renderScene(const Game& game)
{
    myEngine.mvMatrixStack.pushMatrix();

    const float spacing = 1.0f;
    const int rows = 5;
    const int cols = 5;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation({j * spacing, i * spacing, 0.0f});
            myEngine.updateMvMatrix();
            if ((i + j) % 2) // if broken like add condition to change the textures // add randomness
            {
                drawTile(square);
            } else {
                drawTile(square2);
            }
            
            myEngine.mvMatrixStack.popMatrix();
        }
    }

    myEngine.mvMatrixStack.popMatrix();

    game.player->draw(myEngine);
}