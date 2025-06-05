#include "homeScene.hpp"
#include "managers/gameManager.hpp"
#include "managers/menu.hpp"
#include "map/pathfinding.hpp"
#include "managers/texture.hpp"

GLBI_Texture homeTexture;
StandardMesh homeTile;


void drawOneImage(int &x, int &y, StandardMesh &textureTile)
{
    myEngine.setFlatColor(1.0, 1.0, 1.0);
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(static_cast<float>(x), static_cast<float>(y), 0.0));
    myEngine.updateMvMatrix();
    textureTile.draw();
    myEngine.mvMatrixStack.popMatrix();
}

void HomeScene::init()
{
    Texturing::initTexture(homeTexture, "FIRST_SCENE", "png");
    homeTile = Texturing::createMeshImage(800);
    homeTile.createVAO();

}

void HomeScene::update()
{

}

void  HomeScene::draw()
{
    int x, y;
    drawOneImage(x, y, homeTile);
}

void  HomeScene::destroy()
{
    // glDeleteTextures
}