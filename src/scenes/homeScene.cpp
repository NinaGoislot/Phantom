#include "homeScene.hpp"
#include "managers/gameManager.hpp"
#include "managers/menu.hpp"
#include "map/pathfinding.hpp"
#include "managers/texture.hpp"

GLBI_Texture homeTexture;
GLBI_Texture buttonTexture;

StandardMesh homeTile;
StandardMesh buttonTile;
StandardMesh mesh;

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
    Texturing::initTexture(homeTexture, "FIRST_SCENE_RECT", "png");
    homeTile = Texturing::createImageMesh(0,0,1920,1080,1920,1080);
    homeTile.createVAO();

    Texturing::initTexture(buttonTexture, "FIRST_SCENE-button", "png");
    buttonTile = Texturing::createMapTileMesh(0, 0, 245, 245);
    buttonTile.createVAO();
}

void HomeScene::update()
{
}

void drawBackground()
{
    myEngine.activateTexturing(true);
    homeTexture.attachTexture();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0, 0));
    myEngine.mvMatrixStack.addHomothety(25.0);
    // engine.mvMatrixStack.addTranslation(Vector3D(2., 6., 0));
    myEngine.setFlatColor(1.0f, 0.0f, 0.0f); // carré rouge
    myEngine.updateMvMatrix();
    homeTile.draw();
    myEngine.mvMatrixStack.popMatrix();

    homeTexture.detachTexture();
    myEngine.activateTexturing(false);
}

void drawButton()
{
    myEngine.activateTexturing(true);
    buttonTexture.attachTexture();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0, 0));
    myEngine.mvMatrixStack.addHomothety(5.0);
    // engine.mvMatrixStack.addTranslation(Vector3D(2., 6., 0));
    myEngine.setFlatColor(1.0f, 0.0f, 0.0f); // carré rouge
    myEngine.updateMvMatrix();
    buttonTile.draw();
    myEngine.mvMatrixStack.popMatrix();

    buttonTexture.detachTexture();
    myEngine.activateTexturing(false);
}

void HomeScene::draw()
{
    // myEngine.switchToFlatShading();
    drawBackground();
    drawButton();
}

void HomeScene::destroy()
{
    // glDeleteTextures
}

// #include "player.hpp"
// #include "managers/gameManager.hpp"
// #include "scenes/endScene.hpp"

// void Player::init()
// {
//     try
//     {
//         Texturing::initTexture(playerAtlas, "Player", "png");
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Player::init] Erreur lors de l'initialisation de la texture : " << e.what() << std::endl;
//         return;
//     }

//     square = Texturing::createPlayerTileMesh(0);
//     if (!square.createVAO())
//     {
//         std::cerr << "[Player::init] Echec de la création du VAO pour le joueur." << std::endl;
//         return;
//     }

//     std::cout << "[Player::init] Player initialized" << std::endl;
// }

// void Player::setFrame(int frameIndex)
// {
//     currentFrame = frameIndex;
//     Texturing::updateUVs(square, frameIndex, 0, 16.0f, 32.0f, 256.0f, 32.0f);
// }

// void Player::draw(glbasimac::GLBI_Engine &engine)
// {
//     engine.activateTexturing(true);
//     playerAtlas.attachTexture();

//     engine.mvMatrixStack.pushMatrix();
//     engine.mvMatrixStack.addTranslation(Vector3D(position.x, position.y, 0));
//     // engine.mvMatrixStack.addTranslation(Vector3D(2., 6., 0));
//     engine.setFlatColor(1.0f, 0.0f, 0.0f); // carré rouge
//     engine.updateMvMatrix();
//     square.draw();
//     engine.mvMatrixStack.popMatrix();

//     playerAtlas.detachTexture();
//     engine.activateTexturing(false);
// }