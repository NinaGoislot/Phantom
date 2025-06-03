#pragma once

#include "managers/game.hpp"

/* Camera parameters and functions */
extern bool flag_anim_rot_scale;
extern bool flag_anim_rot_arm;

namespace DrawGame
{
    void init();
    void render(const Game &game);
}