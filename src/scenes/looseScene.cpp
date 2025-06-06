#include "looseScene.hpp"
#include "managers/gameManager.hpp"
#include "managers/menu.hpp"
#include "map/pathfinding.hpp"
#include "managers/texture.hpp"

GLBI_Texture looseTexture;
GLBI_Texture looseButtonTexture;

StandardMesh looseTile;
StandardMesh looseButtonTile;

void LooseScene::init()
{
    BUTTON_SIZE_X = 245;
    BUTTON_SIZE_Y = 70;
    BUTTON_OFFSET_X = 0.0f;
    BUTTON_OFFSET_Y = -4.5f;

    Texturing::initTexture(looseTexture, "LOOSE_SCENE_RECT", "png");
    looseTile = Texturing::createImageMesh(0, 0, 1920, 1080, 1920, 1080);
    looseTile.createVAO();

    Texturing::initTexture(looseButtonTexture, "LOOSE_SCENE-button", "png");
    looseButtonTile = Texturing::createImageMesh(0, 0, BUTTON_SIZE_X, BUTTON_SIZE_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y);
    looseButtonTile.createVAO();
}

void LooseScene::update()
{
}

void LooseScene::draw()
{
    myEngine.switchToFlatShading();
    myEngine.mvMatrixStack.loadIdentity();
    drawBackground(looseTexture, looseTile);
    drawButton(looseButtonTexture, looseButtonTile, BUTTON_OFFSET_X, BUTTON_OFFSET_Y);

    int windowX, windowY;
    glfwGetWindowSize(getGame()->window, &windowX, &windowY);
    float aspectRatio = static_cast<float>(windowX) / static_cast<float>(windowY);
    float halfViewX = GL_VIEW_SIZE * aspectRatio / 2;
    float halfViewY = GL_VIEW_SIZE / 2;

    float buttonCenterX = windowX / 2 + (BUTTON_OFFSET_X / (GL_VIEW_SIZE * aspectRatio)) * windowX;
    float buttonCenterY = windowY / 2 - (BUTTON_OFFSET_Y / GL_VIEW_SIZE) * windowY;

    if (controls.isMousePressed(GLFW_MOUSE_BUTTON_LEFT))
    {
        double mouseX, mouseY;
        glfwGetCursorPos(getGame()->window, &mouseX, &mouseY);
        if (mouseX >= (buttonCenterX - BUTTON_SIZE_X / 2) &&
            mouseX <= (buttonCenterX + BUTTON_SIZE_X / 2) &&
            mouseY >= (buttonCenterY - BUTTON_SIZE_Y / 2) &&
            mouseY <= (buttonCenterY + BUTTON_SIZE_Y / 2))
        {
            std::cout << "Button clicked!" << std::endl;
            relaunchGameScene();
        }
    }
}

void LooseScene::destroy()
{
    // glDeleteTextures
}