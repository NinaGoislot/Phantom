#pragma once

#include <random>
#include "glbasimac/glbi_engine.hpp"
#include "tools/basic_mesh.hpp"
#include "managers/game.hpp"


using namespace glbasimac;

/* Camera parameters and functions */
extern bool flag_anim_rot_scale;
extern bool flag_anim_rot_arm;

/* OpenGL Engine */
extern GLBI_Engine myEngine;

void initScene();

void renderScene(const Game& game);

void drawSquare(const StandardMesh& square);

StandardMesh createAutoTiledMesh();

