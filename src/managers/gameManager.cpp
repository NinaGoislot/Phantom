// Opengl
#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include "glbasimac/glbi_texture.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/shaders.hpp"

// External files
#include "controls/controls.hpp"
#include "time.hpp"
#include "scenes/gameScene.hpp"
#include "scenes/homeScene.hpp"
#include "scenes/victoryScene.hpp"
#include "managers/gameManager.hpp"
#include "managers/text.hpp"
#include "characters/villain.hpp"
#include "scenes/gameScene.hpp"
#include "scenes/victoryScene.hpp"
#include "scenes/looseScene.hpp"
#include "scenes/homeScene.hpp"
#include "map/grid.hpp"
#include "map/item.hpp"
#include "map/pathfinding.hpp"

#include "tools/camera.hpp"

// External libs
#include <iostream>
#include <array>
#include <math.h>

void onError(int error, const char *description)
{
    std::cout << "GLFW Error (" << error << ") : " << description << std::endl;
}

void onWindowResized(GLFWwindow * /*window*/, int width, int height)
{
    aspectRatio = width / (float)height;
    glViewport(0, 0, width, height);
    if (aspectRatio > 1.0)
    {
        myEngine.set2DProjection(-GL_VIEW_SIZE * aspectRatio / 2.,
                                 GL_VIEW_SIZE * aspectRatio / 2.,
                                 -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    }
    else
    {
        myEngine.set2DProjection(-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
                                 -GL_VIEW_SIZE / (2. * aspectRatio),
                                 GL_VIEW_SIZE / (2. * aspectRatio));
    }
}

void setupCallbacks(GLFWwindow *window)
{
    // deal with resizing the window
    glfwSetWindowSizeCallback(window, onWindowResized);
    setupControlsCallbacks(window);
}

void createGame(GLFWwindow *window)
{
    std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> grid = generateMap();

    Player *player = new Player{};
    Game *game = new Game{window, player, {}, SceneManager{}, grid};
    glfwSetWindowUserPointer(window, game);
    if (getGame())
    {
        std::cout << "[gameManager] Game created" << std::endl;
    }
    else
    {
        std::cerr << "[gameManager] Failed to create game object" << std::endl;
        exit(EXIT_FAILURE);
    }
    generateFlowField();
    player->init();
    game->phantomsList.push_back(std::make_shared<Villain>());
    for (auto &phantom : game->phantomsList)
    {
        phantom->init();
    }

    launchGameScene();
}

void initGame()
{
    // Initialize the library
    if (!glfwInit())
    {
        std::cerr << "[gameManager] Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    /* Callback to a function if an error is rised by GLFW */
    glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Phantom", /*glfwGetPrimaryMonitor() for fullscreen*/ nullptr, nullptr);
    // GLFWmonitor* monitor = glfwGetWindowMonitor(window);
    // const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    if (!window)
    {
        glfwTerminate();
        std::cerr << "[gameManager] Failed to create GLFW window" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Intialize glad (loads the OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "[gameManager] Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    setupCallbacks(window);

    // sets the window as fullscreen, but unplayable so we disable it for now
    // glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

    // Initialize Rendering Engine
    myEngine.initGL();

    textInit();

    // deal with resizing the window
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    onWindowResized(window, width, height);

    glClearColor(0.2f, 0.f, 0.f, 0.f);

    createGame(window);
}

Game *getGame()
{
    GLFWwindow *window = glfwGetCurrentContext();
    if (!window)
    {
        throw std::runtime_error("[gameManager] GetGame : No current OpenGL context found.");
    }

    Game *game = static_cast<Game *>(glfwGetWindowUserPointer(window));
    if (!game)
    {
        throw std::runtime_error("[gameManager] GetGame : Game object not found via glfwGetWindowUserPointer.");
    }

    return game;
}

std::shared_ptr<Scene> getCurrentScene()
{
    Game *game = getGame();
    auto scene = game->sceneManager.getCurrentScene();
    if (!scene)
    {
        throw std::runtime_error("[GameManager: getCurrentScene] No active scene found in SceneManager.");
    }
    return game->sceneManager.getCurrentScene();
}
Player *getPlayer()
{
    Game *game = getGame();
    if (!game->player)
    {
        throw std::runtime_error("[GameManager: getPlayer] Player pointer is null.");
    }
    return game->player;
}

std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> &getGrid()
{
    Game *game = getGame();
    if (game->grid.empty())
    {
        throw std::runtime_error("[GameManager: getGrid] Grid is empty.");
    }
    return game->grid;
}

void launchVictoryScene()
{
    Game *game = getGame();
    game->sceneManager.setCurrentScene(std::make_shared<VictoryScene>());
}
void launchLooseScene()
{
    Game *game = getGame();
    game->sceneManager.setCurrentScene(std::make_shared<LooseScene>());
};
void launchGameScene()
{
    Game *game = getGame();
    game->sceneManager.setCurrentScene(std::make_shared<GameScene>());
};
void launchHomeScene()
{
    Game *game = getGame();
    game->sceneManager.setCurrentScene(std::make_shared<HomeScene>());
};
