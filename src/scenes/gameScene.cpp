#include "scenes/gameScene.hpp"
#include "managers/gameManager.hpp"
#include "scenes/draw_game.hpp"

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
}

void GameScene::draw()
{
    DrawGame::render(*getGame());
}
void GameScene::destroy()
{
    // glDeleteTextures
}