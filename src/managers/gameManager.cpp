//Opengl
#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include "glbasimac/glbi_texture.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/shaders.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "tools/stb_image.h"

//External files
#include "controls/controls.hpp"
#include "time.hpp"
#include "scenes/gameScene.hpp"
#include "managers/gameManager.hpp"
#include "managers/text.hpp"


//External libs
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

Game createGame(GLFWwindow *window)
{
    Player* player = new Player{};
    player->init();
    Game game{window, player, SceneManager{}};
    game.sceneManager.setCurrentScene(std::make_shared<GameScene>());
    glfwSetWindowUserPointer(window, &game);
    return game;
}

Game initGame(){
    // Initialize the library
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
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
        std::cerr << "Failed to create GLFW window" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Intialize glad (loads the OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

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
    return createGame(window);
}

Game* getGame() {
    GLFWwindow* window = glfwGetCurrentContext();
    if (!window) {
        throw std::runtime_error("GetGame : No current OpenGL context found.");
    }

    Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    if (!game) {
        throw std::runtime_error("GetGame : Game object not found via glfwGetWindowUserPointer.");
    }

    return game;
}
