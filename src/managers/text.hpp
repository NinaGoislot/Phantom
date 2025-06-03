#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "simpletext.h"

void textInit();

std::string textWritten(std::string const& text);

void textDraw(std::string const& text, float x, float y, SimpleText::Color color, SimpleText::Alignment alignment, SimpleText::FontSize size = SimpleText::SIZE_16,
              bool isWriting = false);