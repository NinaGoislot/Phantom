#pragma once
#include <iostream>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include "glbasimac/glbi_engine.hpp"

class Phantom
{
public:
    virtual ~Phantom() = default;

    virtual void init() = 0;
    virtual void move(glm::vec2 direction) = 0;
    virtual void draw(glbasimac::GLBI_Engine& engine) = 0;
    virtual void update() = 0;


    glm::vec2 position{};
    float scale = 1.;
    glm::vec2 size{1, 1.};

    float speed = 5.0f;
};
