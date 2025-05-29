#include "controls.hpp"
#include "characters/player.hpp"
#include <Windows.h>
#include <mmsystem.h>

bool isMoveControl(int key)
{
    return key == GLFW_KEY_UP || key == GLFW_KEY_DOWN ||
           key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT;
}
void updatePlayer(GLFWwindow *window, const float &deltaTime, const int key, Player &player)
{
    if (glfwGetKey(window, key) == GLFW_PRESS)
    {
        glm::vec2 direction{};
        switch (key)
        {
        case GLFW_KEY_LEFT:
            printf("Fleche gauche.\n");
            PlaySound(TEXT("../../assets/sounds/sample.wav"), NULL, SND_FILENAME | SND_ASYNC);
            direction.x -= 1.0f;
            break;
        case GLFW_KEY_RIGHT:
        printf("Fleche droit.\n");
            PlaySound(0,0,0);
            direction.x += 1.0f;
            break;
        case GLFW_KEY_UP:
        printf("Fleche haut.\n");
            direction.y += 1.0f;
            break;
        case GLFW_KEY_DOWN:
        printf("Fleche bas.\n");
            direction.y -= 1.0f;
            break;
        default:
            break;
        }

        // Normalise pour éviter d'aller plus vite en diagonale
        if (glm::length(direction) > 0.0f)
        {
            direction = glm::normalize(direction);
        }

        //afficher le vecteur de direction
        printf("Direction: (%f, %f)\n", direction.x, direction.y);

        player.position += direction * player.speed * deltaTime;

        //Afficher position du joueur
        printf("Position: (%f, %f)\n", player.position.x, player.position.y);
        // Afficher la vitesse du joueur
        printf("Vitesse: %f\n", player.speed);
    
    }
}

void onKeyPress(GLFWwindow *window, const int key, const int scancode, const int action, const int mods)
{
    // Get the game state from the window user pointer
    Game *game = static_cast<Game *>(glfwGetWindowUserPointer(window));
    if (game == nullptr)
    {
        printf("Game not found.\n");
        return;
    }
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (isMoveControl(key))
        {
            updatePlayer(window, *(game->deltaTime), key, *(game->player));
            return;
        }
        else
        {
            const char *keyName = glfwGetKeyName(key, 0);
            if (keyName != nullptr)
            {
                char convertedKey = keyName[0];
                switch (convertedKey)
                {
                case 'q':
                    printf("Touche Q pressée, On ferme toooooout.\n");
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

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