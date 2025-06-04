#include "scenes/gameScene.hpp"
#include "managers/gameManager.hpp"
#include "scenes/draw_game.hpp"
#include "managers/menu.hpp"
#include "map/grid.hpp"

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

    if (controls.isKeyPressed('e')) // digging action
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

    if (controls.isKeyPressed(GLFW_KEY_LEFT))
    {
        if (isAlive(ceil(playerTile.x - 1), floor(playerTile.y)))
        {
            game->player->move_left();
        }
    }
    if (controls.isKeyPressed(GLFW_KEY_RIGHT))
    {
        if (isAlive(floor(playerTile.x + 1), floor(playerTile.y)))
        {
            game->player->move_right();
        }
    }
    if (controls.isKeyPressed(GLFW_KEY_DOWN))
    {
        if (isAlive(round(playerTile.x), round(playerTile.y - 1)))
        {
            game->player->move_down();
        }
    }

    if (controls.isKeyPressed(GLFW_KEY_UP))
    {
        if (isAlive(round(playerTile.x), floor(playerTile.y + 1)))
        {
            game->player->move_up();
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

void GameScene::draw()
{
    DrawGame::render(*getGame());

    displayMenu(0); // Display the menu with item 0
}
void GameScene::destroy()
{
    // glDeleteTextures
}