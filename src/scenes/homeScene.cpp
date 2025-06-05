#include "homeScene.hpp"
#include "managers/gameManager.hpp"
#include "managers/menu.hpp"
#include "map/pathfinding.hpp"
#include "managers/texture.hpp"

GLBI_Texture homeTexture;
GLBI_Texture homeButtonTexture;

StandardMesh homeTile;
StandardMesh homeButtonTile;

void HomeScene::init()
{
    BUTTON_SIZE_X = 245;
    BUTTON_SIZE_Y = 70;
    BUTTON_OFFSET_X = 0.0f;
    BUTTON_OFFSET_Y = -4.5f;

    Texturing::initTexture(homeTexture, "FIRST_SCENE_RECT", "png");
    homeTile = Texturing::createImageMesh(0, 0, 1920, 1080, 1920, 1080);
    homeTile.createVAO();

    Texturing::initTexture(homeButtonTexture, "FIRST_SCENE-button", "png");
    homeButtonTile = Texturing::createImageMesh(0, 0, BUTTON_SIZE_X, BUTTON_SIZE_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y);
    homeButtonTile.createVAO();
}

void HomeScene::update()
{
}

void HomeScene::draw()
{
    // Draw background and button
    drawBackground(homeTexture, homeTile);
    drawButton(homeButtonTexture, homeButtonTile, BUTTON_OFFSET_X, BUTTON_OFFSET_Y);

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
            launchGameScene();
        }
    }
}

void HomeScene::destroy()
{
    // glDeleteTextures
}