#include "looseScene.hpp"
#include "managers/gameManager.hpp"
#include "managers/menu.hpp"
#include "map/pathfinding.hpp"
#include "managers/texture.hpp"

GLBI_Texture endTexture;
GLBI_Texture endButtonTexture;

StandardMesh endTile;
StandardMesh endButtonTile;

void LooseScene::init()
{
    Texturing::initTexture(endTexture, "END_SCENE_RECT", "png");
    endTile = Texturing::createImageMesh(0,0,1920,1080,1920,1080);
    endTile.createVAO();

    Texturing::initTexture(endButtonTexture, "END_SCENE-button", "png");
    endButtonTile = Texturing::createImageMesh(0,0,245,70,245,70);
    endButtonTile.createVAO();
}

void LooseScene::update()
{
}

void drawBackgroundEnd(GLBI_Texture &Texture, StandardMesh &Tile) {
    myEngine.activateTexturing(true);
    Texture.attachTexture();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0, 0));
    myEngine.mvMatrixStack.addHomothety(25.0);
    // engine.mvMatrixStack.addTranslation(Vector3D(2., 6., 0));
    myEngine.setFlatColor(1.0f, 0.0f, 0.0f); // carré rouge
    myEngine.updateMvMatrix();
    Tile.draw();
    myEngine.mvMatrixStack.popMatrix();

    Texture.detachTexture();
    myEngine.activateTexturing(false);
}

void drawButtonEnd(GLBI_Texture &Texture, StandardMesh &Tile)
{
    myEngine.activateTexturing(true);
    Texture.attachTexture();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, -6, 0));
    myEngine.mvMatrixStack.addHomothety(1.5);
    // engine.mvMatrixStack.addTranslation(Vector3D(2., 6., 0));
    myEngine.setFlatColor(1.0f, 0.0f, 0.0f); // carré rouge
    myEngine.updateMvMatrix();
    Tile.draw();
    myEngine.mvMatrixStack.popMatrix();

    Texture.detachTexture();
    myEngine.activateTexturing(false);
}

void LooseScene::draw()
{
    // myEngine.switchToFlatShading();
    drawBackgroundEnd(endTexture, endTile);
    drawButtonEnd(endButtonTexture, endButtonTile);
}
<<<<<<< HEAD:src/scenes/endScene.cpp

void EndScene::destroy()
=======
void LooseScene::destroy()
>>>>>>> main:src/scenes/looseScene.cpp
{
    // glDeleteTextures
}