#pragma once

#include <iostream>
#include <vector>
#define GLFW_INCLUDE_NONE
// #include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "managers/time.hpp"

struct Player
{
    glm::vec2 position {};
    float scale = 1.;
    glm::vec2 size {1,1.};

    float speed = 5.0f;

    void init();
    void draw(glbasimac::GLBI_Engine& engine);
    glbasimac::GLBI_Convex_2D_Shape square;
    
    void move_up();
    void move_down();
    void move_left();
    void move_right();
    void move(glm::vec2 direction);
};

