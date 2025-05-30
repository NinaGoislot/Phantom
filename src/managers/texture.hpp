#pragma once

#include <vector>
#include <cmath>
#include "glbasimac/glbi_texture.hpp"
#include "glbasimac/glbi_engine.hpp"
#include "tools/basic_mesh.hpp"
#include "tools/shaders.hpp"

namespace Texturing {
    StandardMesh createAutoTiledMesh(float uvSize);
    StandardMesh createPlayerTileMesh(int frameIndex, float tileWidth = 16.0f, float tileHeight = 32.0f, float atlasWidth = 256.0f, float atlasHeight = 32.0f);
    void initTexture(glbasimac::GLBI_Texture& textureAtlas, std::string const atlasName, std::string const ext);
}