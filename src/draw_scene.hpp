#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"

#include "controls/controls.hpp"
#include "game.hpp"


using namespace glbasimac;

/* Camera parameters and functions */
extern bool flag_anim_rot_scale;
extern bool flag_anim_rot_arm;

/* OpenGL Engine */
extern GLBI_Engine myEngine;

void initScene();

void renderScene(const Game& game);

