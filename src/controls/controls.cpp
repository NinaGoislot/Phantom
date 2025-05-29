#include "controls.hpp"
#include "characters/player.hpp"
#include "managers/game.hpp"
#include "managers/time.hpp"

namespace Controls
{
    std::unordered_map<int, bool> _keysState;
}

bool isMoveControl(int key)
{
    return key == GLFW_KEY_UP || key == GLFW_KEY_DOWN ||
           key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT;
}
void updatePlayer(GLFWwindow *window, const int key, Player &player)
{
    glm::vec2 direction{};
    if (Controls::_keysState[GLFW_KEY_LEFT])
    {
        player.move_left();
    }
    if (Controls::_keysState[GLFW_KEY_RIGHT])
    {
        player.move_right();
    }
    if (Controls::_keysState[GLFW_KEY_UP])
    {
        player.move_top();
    }
    if (Controls::_keysState[GLFW_KEY_DOWN])
    {
        player.move_bottom();
    }
}

// void key_callback(int key, int /*scancode*/, int action, int mods)
// {
//     // update _keysState
//     if (key >= 0 && key < _keysState.size())
//     {
//         _keysState[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
//     }
// }

void onKeyPress(GLFWwindow *window, const int key, const int scancode, const int action, const int mods)
{
    int convertedKey = key;
    // Get the game state from the window user pointer
    Game *game = static_cast<Game *>(glfwGetWindowUserPointer(window));
    if (game == nullptr)
    {
        printf("Game not found.\n");
        return;
    }

    if (!isMoveControl(key))
    {
        const char *keyName = glfwGetKeyName(key, 0);
        if (key >= 0 && keyName != nullptr)
        {
            convertedKey = keyName[0];
        }
    }

    if (key >= 0)
    {
        Controls::_keysState[convertedKey] = action == GLFW_PRESS || action == GLFW_REPEAT;
    }

    printf("Condition is: %d\n", action == GLFW_PRESS || action == GLFW_REPEAT);
    printf("okay ?: %d\n", Controls::_keysState[convertedKey]);
    printf("---------------------------------------------------\n");

    updatePlayer(window, key, *(game->player));
}

// void onKeyPress(GLFWwindow *window, const int key, const int scancode, const int action, const int mods)
// {
//     // Get the game state from the window user pointer
//     Game *game = static_cast<Game *>(glfwGetWindowUserPointer(window));
//     if (game == nullptr)
//     {
//         printf("Game not found.\n");
//         return;
//     }

//     if (action == GLFW_PRESS || action == GLFW_REPEAT)
//     {
//         if (isMoveControl(key))
//         {
//             updatePlayer(window,  key, *(game->player));
//             return;
//         }
//         else
//         {
//             const char *keyName = glfwGetKeyName(key, 0);
//             if (keyName != nullptr)
//             {
//                 char convertedKey = keyName[0];
//                 switch (convertedKey)
//                 {
//                 case 'q':
//                     printf("Touche Q pressée, On ferme toooooout.\n");
//                     glfwSetWindowShouldClose(window, GLFW_TRUE);
//                     break;
//                 default:
//                     break;
//                 }
//             }
//         }
//     }
// }

void onMouseMove(GLFWwindow *window, double xpos, double ypos)
{
    // stuff here if needed
}

void onClick(GLFWwindow *window, int button, int action, int mods)
{
}

void Controls::setupCallbacks(GLFWwindow *window)
{
    glfwSetKeyCallback(window, onKeyPress);
    glfwSetCursorPosCallback(window, onMouseMove);
    glfwSetMouseButtonCallback(window, onClick);
}

// char convertKey_char(int key)
// {
//     // Convert the key to a char
//     const char *keyName = glfwGetKeyName(key, 0);
//     if (keyName != nullptr)
//     {
//         return keyName[0];
//     }
//     return -1;
// }

// char convertKey_int(char key)
// {
//     // Convert the key to a char
//     const char *keyName = glfwGetKeyName(key, 0);
//     if (keyName != nullptr)
//     {
//         return keyName[0];
//     }
//     return -1;
// }

// void updatePlayer(GLFWwindow *window, const int key, Player &player)
// {
//     if (glfwGetKey(window, key) == GLFW_PRESS)
//     {
//         glm::vec2 direction{};
//         switch (key)
//         {
//         case GLFW_KEY_LEFT:
//             printf("Fleche gauche.\n");
//             player.move_left();
//             break;
//         case GLFW_KEY_RIGHT:
//             printf("Fleche droit.\n");
//             player.move_right();
//             break;
//         case GLFW_KEY_UP:
//             printf("Fleche haut.\n");
//             player.move_top();
//             break;
//         case GLFW_KEY_DOWN:
//             printf("Fleche bas.\n");
//             player.move_bottom();
//             break;
//         default:
//             break;
//         }
//     }
// }