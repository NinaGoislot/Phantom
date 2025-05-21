#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "simpletext.h"

void textInit();

void textDraw(std::string text, float x, float y, SimpleText::Alignment alignment, SimpleText::FontSize size = SimpleText::SIZE_16);