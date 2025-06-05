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

    StandardMesh square;
    glbasimac::GLBI_Texture villainAtlas;
};
