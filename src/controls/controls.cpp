#include "controls.hpp"
#include "characters/player.hpp"
#include "managers/gameManager.hpp"
#include "managers/time.hpp"
#include "map/grid.hpp"

bool isMoveControl(int key, Controls &controls)
{
    for (const int &moveKey : controls.moveControls)
    {
        if (key == moveKey)
        {
            return true;
        }
    }
    return false;
}

void onKeyPress(GLFWwindow *window, const int key, const int scancode, const int action, const int mods)
{
    int convertedKey = key;
    // Get the game state from the window user pointer
    Game *game = getGame();
    auto currentScene = game->sceneManager.getCurrentScene();
    if (!currentScene)
    {
        throw std::runtime_error("Aucune scène active trouvée dans SceneManager.");
    }

    if (!isMoveControl(key, currentScene->controls))
    {
        const char *keyName = glfwGetKeyName(key, 0);
        if (key >= 0 && keyName != nullptr)
        {
            convertedKey = keyName[0];
        }
    }

    if (key >= 0)
    {
        bool pressed = action == GLFW_PRESS || action == GLFW_REPEAT;
        currentScene->controls.setKeyState(convertedKey, pressed);
    }
}

void onMouseMove(GLFWwindow *window, double xpos, double ypos)
{
    // stuff here if needed
}

void onClick(GLFWwindow *window, int button, int action, int mods)
{
}

void Controls::setKeyState(int key, bool isPressed)
{
    keyStates[key] = isPressed;
}

bool Controls::isKeyPressed(int key) const
{
    auto key_it = keyStates.find(key);
    return key_it != keyStates.end() && key_it->second;
}

void Controls::reset()
{
    for (auto &[key, state] : keyStates)
    {
        state = false;
    }
}

int Controls::nbMoveControlsActive()
{
    int count = 0;
    for (const int &key : moveControls)
    {
        if (isKeyPressed(key))
        {
            count++;
        }
    }
    return count;
}

void setupControlsCallbacks(GLFWwindow *window)
{
    glfwSetKeyCallback(window, onKeyPress);
    glfwSetCursorPosCallback(window, onMouseMove);
    glfwSetMouseButtonCallback(window, onClick);
}
