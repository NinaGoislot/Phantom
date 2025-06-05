#include "scenes/gameScene.hpp"
#include "managers/gameManager.hpp"
#include "scenes/draw_game.hpp"
#include "managers/menu.hpp"
#include "map/pathfinding.hpp"
#include "map/item.hpp"
#include "map/trap.hpp"
#include "map/obstacle.hpp"

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
        glm::vec2 playerPos = game->player->getPosition();

        glm::vec2 offset(50.0f, 50.0f);            // not same coords between map and player
        glm::vec2 playerTile = playerPos + offset; // we need to add 50 to each axis

        std::vector<bool> conditions{
            isAlive(ceil(playerTile.x - 1), floor(playerTile.y)),  // LEFT
            isAlive(floor(playerTile.x + 1), floor(playerTile.y)), // RIGHT
            isAlive(round(playerTile.x), round(playerTile.y - 1)), // DOWN
            isAlive(round(playerTile.x), floor(playerTile.y + 1))  // UP
        };

        std::vector<glm::vec2> digOffsets{
            {-0.5, 0}, // LEFT
            {0.5, 0},  // RIGHT
            {0, -1.0}, // DOWN
            {0, 0.5}   // UP
        };

        if (controls.nbMoveControlsActive() < 2)
        {
            if (controls.isKeyPressed(GLFW_KEY_LEFT) || controls.isKeyPressed('q'))
            {
                int targetX = ceil(playerTile.x - 1);
                int targetY = floor(playerTile.y);
                if (isAlive(targetX, targetY) && !isObstacleAt(targetX, targetY))
                {
                    game->player->move_left();
                }
            }
            if (controls.isKeyPressed(GLFW_KEY_RIGHT) || controls.isKeyPressed('d'))
            {
                int targetX = floor(playerTile.x + 1);
                int targetY = floor(playerTile.y);
                if (isAlive(targetX, targetY) && !isObstacleAt(targetX, targetY))
                {
                    game->player->move_right();
                }
            }
            if (controls.isKeyPressed(GLFW_KEY_DOWN) || controls.isKeyPressed('s'))
            {
                int targetX = round(playerTile.x);
                int targetY = round(playerTile.y - 1);
                if (isAlive(targetX, targetY) && !isObstacleAt(targetX, targetY))
                {
                    game->player->move_down();
                }
            }
            if (controls.isKeyPressed(GLFW_KEY_UP) || controls.isKeyPressed('z'))
            {
                int targetX = round(playerTile.x);
                int targetY = floor(playerTile.y + 1);
                if (isAlive(targetX, targetY) && !isObstacleAt(targetX, targetY))
                {
                    game->player->move_up();
                }
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

        game->player->isMoving = controls.nbMoveControlsActive() > 0;

        if (game->player->isMoving)
        {
            generateFlowField();

            // Afficher le flow field dans la console
            for (int y = 0; y < MAP_HEIGHT; ++y)
            {
                for (int x = 0; x < MAP_WIDTH; ++x)
                {
                    const Cell &cell = game->grid[y][x];
                    if (cell.direction == glm::ivec2{0, 0})
                    {
                        std::cout << ". "; // Cellule sans direction
                    }
                    else
                    {
                        std::cout << "(" << cell.direction.x << "," << cell.direction.y << ") ";
                    }
                }
                std::cout << std::endl;
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

        if (controls.isKeyPressed('a'))
        {
            try
            {
                for (size_t i = 0; i < conditions.size(); ++i)
                {
                    if (!conditions[i]) // If not alive, dig it
                    {
                        int digX = round(playerTile.x + digOffsets[i].x);
                        int digY = round(playerTile.y + digOffsets[i].y);
                        digTile(digX, digY);
                        break; // Dig only one tile
                    }
                }
            }

            catch (const std::exception &e)
            {
                std::cerr << "[GameScene::update] dig impossible " << e.what() << '\n';
            }
        }

        bool isSoftLocked{((!isAlive(round(playerTile.x), round(playerTile.y - 1)) &&
                            !isAlive(round(playerTile.x), floor(playerTile.y + 1)) &&
                            !isAlive(floor(playerTile.x + 1), floor(playerTile.y)) &&
                            !isAlive(ceil(playerTile.x - 1), floor(playerTile.y))))};

        if (isSoftLocked)
        {
            int maxAttempts = 5;
            int attempts = 0;

            while (attempts < maxAttempts)
            {
                game->player->move_up();
                attempts++;

                glm::vec2 newPlayerPos = game->player->getPosition();
                glm::vec2 newPlayerTile = newPlayerPos + offset;

                if (!isSoftLocked)
                {
                    break; // Player is no longer softlocked
                }
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