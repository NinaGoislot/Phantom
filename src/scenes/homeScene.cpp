#include "homeScene.hpp"
#include "managers/gameManager.hpp"
#include "managers/menu.hpp"
#include "map/pathfinding.hpp"
#include "managers/texture.hpp"

GLBI_Texture homeTexture;
GLBI_Texture homeButtonTexture;

StandardMesh homeTile;
StandardMesh homeButtonTile;
StandardMesh mesh;

void HomeScene::init()
{
    Texturing::initTexture(homeTexture, "FIRST_SCENE_RECT", "png");
    homeTile = Texturing::createImageMesh(0,0,1920,1080,1920,1080);
    homeTile.createVAO();

    Texturing::initTexture(homeButtonTexture, "FIRST_SCENE-button", "png");
    homeButtonTile = Texturing::createImageMesh(0,0,245,70,245,70);
    homeButtonTile.createVAO();
}

void HomeScene::update()
{

}


void drawBackgroundHome(GLBI_Texture &Texture, StandardMesh &Tile) {
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

void drawButtonHome(GLBI_Texture &Texture, StandardMesh &Tile)
{
    myEngine.activateTexturing(true);
    Texture.attachTexture();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, -4.5, 0));
    myEngine.mvMatrixStack.addHomothety(1.5);
    // engine.mvMatrixStack.addTranslation(Vector3D(2., 6., 0));
    myEngine.setFlatColor(1.0f, 0.0f, 0.0f); // carré rouge
    myEngine.updateMvMatrix();
    Tile.draw();
    myEngine.mvMatrixStack.popMatrix();

    Texture.detachTexture();
    myEngine.activateTexturing(false);
}

void HomeScene::draw()
{
    // myEngine.switchToFlatShading();
    drawBackgroundHome(homeTexture, homeTile);
    drawButtonHome(homeButtonTexture, homeButtonTile);
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