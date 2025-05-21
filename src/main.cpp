#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include <iostream>
#include <array>
#include <math.h>
#include "draw_scene.hpp"
#include "map.hpp"

using namespace glbasimac;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static float aspectRatio = 1.0f;
static const float GL_VIEW_SIZE = 40.; // changed to 40 here
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 800;
static bool minusAngleActivated = false;

static bool color_mode_activated = true;
static std::array<float, 4> base_rgba{0.f, 0.f, 0.f, 0.f};

/* Error handling function */
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

bool shiftPressed = false;
bool lineMode = false;

void onKeyDown(GLFWwindow *window, int key, int scancode, int action, int mods)
{

    const char *key_name = glfwGetKeyName(key, 0);

    // std::cout << key_name << std::endl;
    // we want to exit on the q key but we are baguettes so here we need to set it to the A
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

static void onMouseMove(GLFWwindow *window, double xpos, double ypos)
{
    // stuff here if needed
}

void onClick(GLFWwindow *window, int button, int action, int mods)
{

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        minusAngleActivated = false;
        double xpos, ypos;
        // getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);

        int height, width;
        // getting window size
        glfwGetWindowSize(window, &width, &height);
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        minusAngleActivated = true;
    }
}

int main()
{
    // Initialize the library
    if (!glfwInit())
    {
        return -1;
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
        return -1;
    }

    // deal with resizing the window
    glfwSetWindowSizeCallback(window, onWindowResized);

    // sets the window as fullscreen, but unplayable so we disable it for now
    // glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

    // deal with exit button - q
    glfwSetKeyCallback(window, onKeyDown);

    glfwSetCursorPosCallback(window, onMouseMove);
    glfwSetMouseButtonCallback(window, onClick);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Intialize glad (loads the OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    // Initialize Rendering Engine
    myEngine.initGL();


    // Initializing the scene
    initScene();

    // deal with resizing the window
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    onWindowResized(window, width, height);

    // deal with closing the window

    onKeyDown(window, GLFW_KEY_A, GLFW_PRESS, 0, 0);

    if (color_mode_activated)
    {
        onClick(window, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    }

    glClearColor(0.2f, 0.f, 0.f, 0.f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Get time (in second) at loop beginning */
        double startTime = glfwGetTime();

        /* Render here */

        glClear(GL_COLOR_BUFFER_BIT);
        if (!color_mode_activated)
        {
            glClearColor(base_rgba[0], base_rgba[1], base_rgba[2], base_rgba[3]);
        }

        // render here

        renderScene();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        /* Elapsed time computation from loop begining */
        double elapsedTime = glfwGetTime() - startTime;
        /* If to few time is spend vs our wanted FPS, we wait */
        while (elapsedTime < FRAMERATE_IN_SECONDS)
        {
            glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
            elapsedTime = glfwGetTime() - startTime;
        }
    }

    glfwTerminate();
    return 0;
}
