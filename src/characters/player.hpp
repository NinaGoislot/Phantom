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
#include "glbasimac/glbi_texture.hpp"
#include "tools/basic_mesh.hpp"
#include "managers/time.hpp"
#include "managers/texture.hpp"

struct Player
{
    //------------------------------------
    //-------------- PARAMS --------------
    //------------------------------------
    glm::vec2 position{};
    float scale = 1.;
    glm::vec2 size{1, 1.};

    float speed = 5.0f;
    bool isMoving = false;

    int life {3};

    //------------------------------------
    //------------- FUNCTION -------------
    //------------------------------------

    void init();
    void draw(glbasimac::GLBI_Engine &engine);
    void takeDamage(int damage = 1);

    //------------------------------------
    //-------------- GETTERS -------------
    //------------------------------------

    glm::vec2 getPosition();

    //------------------------------------
    //------------- ANIMATION ------------
    //------------------------------------
    StandardMesh square;
    glbasimac::GLBI_Texture playerAtlas;
    int currentFrame = 0;
    int frameDirection = 0;
    int animationStep = 0;
    float frameDuration = 0.2f; // seconds per animation frame
    float animationTimer = 0.0f;
    int lastFrameDirection = -1;

    void anim_up();
    void anim_down();
    void anim_left();
    void anim_right();

    void move_up();
    void move_down();
    void move_left();
    void move_right();
    void move(glm::vec2 direction);
    void setFrame(int frameIndex);
    void updateAnimatedFrame();
};
