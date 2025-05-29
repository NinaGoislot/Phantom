#pragma once

#include <vector>
#include <cmath>
#include "glbasimac/glbi_texture.hpp"
#include "glbasimac/glbi_engine.hpp"
#include "tools/basic_mesh.hpp"
#include "tools/shaders.hpp"

namespace Texturing {
    StandardMesh createAutoTiledMesh(float uvSize);
    void initTexture(glbasimac::GLBI_Texture& textureAtlas);
}