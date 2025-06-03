#include <iostream>
#include <array>
#include <math.h>
#include "controls/controls.hpp"
#include "characters/player.hpp"
#include "managers/game.hpp"
#include "managers/time.hpp"

static bool color_mode_activated = true;
static std::array<float, 4> base_rgba{0.f, 0.f, 0.f, 0.f};

int main()
{
    Game game = initGame();
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(game.window))
    {
        get_loop_time().updateTime();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        if (!color_mode_activated)
        {
            glClearColor(base_rgba[0], base_rgba[1], base_rgba[2], base_rgba[3]);
        }

        // render here
        game.sceneManager.getCurrentScene()->update();
        game.sceneManager.getCurrentScene()->draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(game.window);

        /* Poll for and process events */ //Met en place les keycallback
        glfwPollEvents();

        /* Elapsed time computation from loop begining */
        
        // double frameEndTime = glfwGetTime();
        // double elapsedTime = glfwGetTime() - LoopTime::startTime;
        // /* If to few time is spend vs our wanted FPS, we wait */
        // while (elapsedTime < FRAMERATE_IN_SECONDS)
        // {
        //     glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
        //     elapsedTime = glfwGetTime() - LoopTime::startTime;
        // }

        // LoopTime::updateTime();
    }

    glfwTerminate();
    return 0;
}
