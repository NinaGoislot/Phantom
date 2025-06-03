#include "time.hpp"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

// void initTime()
// {
// }

// void LoopTime::setTime()
// {
//     /* Get time (in second) at loop beginning */
//     LoopTime::startTime = glfwGetTime();
//     LoopTime::currentTime = glfwGetTime();
//     LoopTime::deltaTime = LoopTime::currentTime - LoopTime::previousTime;
// }

void LoopTime::updateTime()
{
   previousTime = currentTime;
    currentTime = glfwGetTime();
    deltaTime = currentTime - previousTime;
}