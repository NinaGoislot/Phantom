#pragma once
#include <iostream>
#include "controls/controls.hpp"

class Scene {
public:
    virtual ~Scene() = default;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void destroy() = 0;

    Controls controls{};

    bool isActive = true; // Désactiver une scène sans la détruire
};
