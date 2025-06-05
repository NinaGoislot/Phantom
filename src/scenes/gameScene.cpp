#include "scenes/gameScene.hpp"
#include "managers/gameManager.hpp"
#include "scenes/draw_game.hpp"
#include "managers/menu.hpp"
#include "map/item.hpp"
#include "map/trap.hpp"

void GameScene::init()
{
    DrawGame::init();
}

void GameScene::update()
{
    Game *game = getGame();
    auto currentScene = game->sceneManager.getCurrentScene();

    glm::vec2 pos = game->player->getPosition();

    try
    {
        for (auto &oneTrap : traps())
        {
            if (oneTrap.positionX == round(pos.x + 50) &&
                oneTrap.positionY == floor(pos.y + 50))
            {

                std::cout << "Player stepped on trap ID: " << oneTrap.id << std::endl;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "[GameScene::update] Erreur durant la détection de collision avec un piège : " << e.what() << std::endl;
        throw;
    }

    try
    {
        if (controls.nbMoveControlsActive() < 2)
        {
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

        if (controls.isKeyPressed('a'))
        {
            glm::vec2 pos = game->player->getPosition();
            try
            {
                digTile(static_cast<int>(round(pos.x + 50)), static_cast<int>(round(pos.y + 50)));
            }
            catch (const std::exception &e)
            {
                std::cerr << "[GameScene::update] dig impossible " << e.what() << '\n';
            }
        }
        if (controls.isKeyPressed('e'))
        {
            getItem(items());
        }
        if (controls.isKeyPressed('f'))
        {
            displayItems(items());
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "[GameScene::update] Erreur durant input ou mouvement : " << e.what() << std::endl;
        throw;
    }
}

void GameScene::draw()
{
    DrawGame::render(*getGame());

    displayMenu(countItemsCollected(items()));
    // try
    // {
    //     displayMenu(0);
    // }
    // catch (const std::exception &e)
    // {
    //     std::cerr << "[GameScene::draw] Erreur dans displayMenu() : " << e.what() << std::endl;
    // }
}
void GameScene::destroy()
{
    // glDeleteTextures
}