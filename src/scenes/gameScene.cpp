#include "scenes/gameScene.hpp"
#include "managers/gameManager.hpp"
#include "scenes/draw_game.hpp"
#include "managers/menu.hpp"

void GameScene::init()
{
    DrawGame::init();
}

void GameScene::update()
{
    Game *game = getGame();
    auto currentScene = game->sceneManager.getCurrentScene();
    if (!currentScene)
    {
        throw std::runtime_error("Aucune scène active trouvée dans SceneManager.");
    }

    if (controls.isKeyPressed(GLFW_KEY_LEFT))
    {
        game->player->move_left();
    }
    if (controls.isKeyPressed(GLFW_KEY_RIGHT))
    {
        game->player->move_right();
    }
    if (controls.isKeyPressed(GLFW_KEY_UP))
    {
        game->player->move_up();
    }
    if (controls.isKeyPressed(GLFW_KEY_DOWN))
    {
        game->player->move_down();
    }
    if (controls.isKeyPressed('s'))
    {
        glm::vec2 playerPos = game->player->getPosition();
        // TO FIX TO WHEN WE'D HAVE COLLISIONS
        digTile(round(playerPos.x+50), round(playerPos.y+50));  // add 50 because the map coords don't have negatives
    }
}

void GameScene::draw()
{
    DrawGame::render(*getGame());

    displayMenu(0); // Display the menu with item 0
}
void GameScene::destroy()
{
    // glDeleteTextures
}