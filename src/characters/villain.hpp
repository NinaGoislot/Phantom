#pragma once
#include "characters/phantom.hpp"
#include "managers/gameManager.hpp"
#include <glm/gtx/norm.hpp> // pour distance2 (plus rapide que distance)
#include <cmath>

struct Villain : public Phantom
{
    Villain() = default;
    void init() override;
    void move(glm::vec2 direction) override;
    void update();
    void draw(glbasimac::GLBI_Engine &engine) override;
    glm::ivec2 convertToGridCoordinates(glm::vec2 position) override;
    void checkIfPlayerIsTouched(const glm::vec2 &position) override;

    //------------------------------------
    //------------- ANIMATION ------------
    //------------------------------------
    StandardMesh square;
    glbasimac::GLBI_Texture villainAtlas;
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
    void setFrame(int frameIndex);
    void updateAnimatedFrame();
};
