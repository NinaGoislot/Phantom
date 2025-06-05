#include "scenes/gameScene.hpp"
#include "managers/gameManager.hpp"
#include "scenes/draw_game.hpp"
#include "managers/menu.hpp"
#include "map/pathfinding.hpp"

void GameScene::init()
{
    DrawGame::init();
}

void GameScene::update()
{
    Game *game = getGame();
    auto currentScene = game->sceneManager.getCurrentScene();

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

        game->player->isMoving = controls.nbMoveControlsActive() > 0;

        if (game->player->isMoving)
        {
            // generateFlowField();

            // Afficher le flow field dans la console
            // for (int y = 0; y < MAP_HEIGHT; ++y)
            // {
            //     for (int x = 0; x < MAP_WIDTH; ++x)
            //     {
            //         const Cell &cell = game->grid[y][x];
            //         if (cell.direction == glm::ivec2{0, 0})
            //         {
            //             std::cout << ". "; // Cellule sans direction
            //         }
            //         else
            //         {
            //             std::cout << "(" << cell.direction.x << "," << cell.direction.y << ") ";
            //         }
            //     }
            //     std::cout << std::endl;
            // }
        }

        if (controls.isKeyPressed('s'))
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
    }
    catch (const std::exception &e)
    {
        std::cerr << "[GameScene::update] Erreur durant input ou mouvement : " << e.what() << std::endl;
        throw;
    }

    for (auto &phantom : game->phantomsList)
    {
        if (phantom)
        {
            phantom->update();
        }
    }
}

void GameScene::draw()
{
    DrawGame::render(*getGame());

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