#pragma once

#include <vector>
#include <glm/glm.hpp>

// struct Cell {
//     glm::ivec2 direction {0, 0};
//     bool walkable {false};
// };

// std::vector<std::vector<Cell>> grid; // vecteur de vecteur, grille colonne par ligne

void generateFlowField(glm::ivec2 targetPos);

