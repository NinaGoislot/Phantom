#pragma once

#include <vector>
#include <glm/glm.hpp>

struct Cell {
    glm::vec2 direction;
    bool walkable {true};
    bool visited {false};
};

std::vector<std::vector<Cell>> grid; // vecteur de vecteur, grille colonne par ligne

void generateFlowField(glm::ivec2 targetPos);

