#include "scenes/victoryScene.hpp"
#include "managers/gameManager.hpp"
#include "managers/menu.hpp"
#include "map/pathfinding.hpp"
#include "managers/texture.hpp"

GLBI_Texture endTexture;
GLBI_Texture endButtonTexture;

StandardMesh endTile;
StandardMesh endButtonTile;

void VictoryScene::init()
{
    BUTTON_SIZE_X = 245;
    BUTTON_SIZE_Y = 70;
    BUTTON_OFFSET_X = 0.0f;
    BUTTON_OFFSET_Y = -6.f;

    Texturing::initTexture(endTexture, "END_SCENE_RECT", "png");
    endTile = Texturing::createImageMesh(0,0,1920,1080,1920,1080);
    endTile.createVAO();

    Texturing::initTexture(endButtonTexture, "END_SCENE-button", "png");
    endButtonTile = Texturing::createImageMesh(0, 0, BUTTON_SIZE_X, BUTTON_SIZE_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y);
    endButtonTile.createVAO();
}

void VictoryScene::update()
{
}

void VictoryScene::draw()
{
    myEngine.switchToFlatShading();
    myEngine.mvMatrixStack.loadIdentity();
    drawBackground(endTexture, endTile);
    drawButton(endButtonTexture, endButtonTile, BUTTON_OFFSET_X, BUTTON_OFFSET_Y);

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
            glfwSetWindowShouldClose(getGame()->window, GLFW_TRUE);
        }
    }
}
void VictoryScene::destroy()
{
    // glDeleteTextures
}