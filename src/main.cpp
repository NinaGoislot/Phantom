#include <iostream>
#include <array>
#include <math.h>
#include "controls/controls.hpp"
#include "characters/player.hpp"
#include "managers/gameManager.hpp"
#include "managers/time.hpp"

static std::array<float, 4> base_rgba{0.f, 0.f, 0.f, 0.f};

void cleanupGame()
{
    Game *game = getGame();
    if (game)
    {
        delete game->player;
        delete game;
    }
}

int main()
{
    try
    {
        initGame();
        Game *game = getGame();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(glfwGetCurrentContext()))
        {
            get_loop_time().updateTime();

            glClear(GL_COLOR_BUFFER_BIT);

            // render here
            game->sceneManager.getCurrentScene()->update();
            game->sceneManager.getCurrentScene()->draw();

            /* Swap front and back buffers */
            glfwSwapBuffers(glfwGetCurrentContext());

            /* Poll for and process events */ // Met en place les keycallback
            glfwPollEvents();
        }

        cleanupGame();

        glfwTerminate();
    }
    catch (const std::exception &e)
    {
        std::cerr << "[main] Exception non geree : " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}