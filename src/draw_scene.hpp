#pragma once

#include <random>
#include "glbasimac/glbi_engine.hpp"
#include "tools/basic_mesh.hpp"
#include "managers/texture.hpp"
#include "managers/game.hpp"
#include <unordered_map>


using namespace glbasimac;

/* OpenGL Engine */
extern GLBI_Engine myEngine;

void initScene();

void renderScene(const Game& game);

void drawSquare(const StandardMesh& square);

void drawOneTile(int& x, int& y, StandardMesh& textureTile);

