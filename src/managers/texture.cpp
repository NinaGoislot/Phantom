#include <vector>
#include <cmath>
#include "glbasimac/glbi_texture.hpp"
#include "tools/shaders.hpp"
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION // va avec
#include "tools/stb_image.h"     // doit être présent qu'une seule fois dans le programme et dans un cpp
#include "glbasimac/glbi_engine.hpp"

#include "texture.hpp"
#include "managers/gameManager.hpp"

using namespace glbasimac;

namespace Texturing
{
    StandardMesh createPlayerTileMesh(int frameIndex, float tileWidth, float tileHeight, float atlasWidth, float atlasHeight)
    {
        if (tileWidth <= 0 || tileHeight <= 0 || atlasWidth <= 0 || atlasHeight <= 0)
        {
            std::cerr << "[createPlayerTileMesh] Invalides sizes : "
                      << "tile(" << tileWidth << "x" << tileHeight << "), atlas(" << atlasWidth << "x" << atlasHeight << ")" << std::endl;
            throw std::runtime_error("createPlayerTileMesh: Dimensions invalides.");
        }

        // Basic quad positions (centered)
        float positions[] = {
            -0.5f, -1.0f, // bottom-left
            0.5f, -1.0f,  // bottom-right
            0.5f, 1.0f,   // top-right
            -0.5f, 1.0f   // top-left
        };

        // Calculate normalized UVs
        float u0 = (frameIndex * tileWidth) / atlasWidth;
        float v0 = 0.0f;
        float u1 = ((frameIndex + 1) * tileWidth) / atlasWidth;
        float v1 = tileHeight / atlasHeight;

        float uvs[] = {
            u0, v0,
            u1, v0,
            u1, v1,
            u0, v1};

        StandardMesh mesh(4, GL_TRIANGLE_FAN);
        mesh.setNbElt(4);
        mesh.addOneBuffer(0, 2, positions, "position", true);
        mesh.addOneBuffer(2, 2, uvs, "texcoord", true);
        return mesh;
    }

    StandardMesh createMapTileMesh(int row, int col, int tileSize, int atlasSize)
    {
        if (tileSize <= 0 || atlasSize <= 0)
        {
            std::cerr << "[createMapTileMesh] Invalide settings : tileSize = " << tileSize << ", atlasSize = " << atlasSize << std::endl;
            throw std::runtime_error("Parametres invalides pour createMapTileMesh.");
        }
        const int atlasCols = atlasSize / tileSize;
        const int atlasRows = atlasSize / tileSize;

        // Normalized UVs
        float tileWidth = static_cast<float>(tileSize) / atlasSize;
        float tileHeight = static_cast<float>(tileSize) / atlasSize;

        float u0 = col * tileWidth;
        float v0 = 1.0f - (row + 1) * tileHeight;
        float u1 = u0 + tileWidth;
        float v1 = v0 + tileHeight;

        // Quad vertex positions (can adjust if tile aspect is not 1:1)
        float positions[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f};

        float uvs[] = {
            u0, v0,
            u1, v0,
            u1, v1,
            u0, v1};

        StandardMesh mesh(4, GL_TRIANGLE_FAN);
        mesh.setNbElt(4);
        mesh.addOneBuffer(0, 2, positions, "position", true);
        mesh.addOneBuffer(2, 2, uvs, "texcoord", true);
        return mesh;
    }

    StandardMesh createImageMesh(int row, int col, int tileWidth, int tileHeight, int atlasWidth, int atlasHeight)
    {
        if (tileWidth <= 0 || tileHeight <= 0 || atlasWidth <= 0 || atlasHeight <= 0)
        {
            std::cerr << "[createMapTileMesh] Invalid settings : tileWidth = " << tileWidth
                      << ", tileHeight = " << tileHeight
                      << ", atlasWidth = " << atlasWidth
                      << ", atlasHeight = " << atlasHeight << std::endl;
            throw std::runtime_error("Invalid parameters for createMapTileMesh.");
        }

        // Normalized UVs (tile size relative to atlas size)
        float tileWidthNorm = static_cast<float>(tileWidth) / atlasWidth;
        float tileHeightNorm = static_cast<float>(tileHeight) / atlasHeight;

        float u0 = col * tileWidthNorm;
        float v0 = 1.0f - (row + 1) * tileHeightNorm; // assuming v=0 at bottom
        float u1 = u0 + tileWidthNorm;
        float v1 = v0 + tileHeightNorm;

        // Adjust quad vertex positions according to tile aspect ratio
        // Positions define a quad centered at origin
        float aspectRatio = static_cast<float>(tileWidth) / tileHeight;

        float halfWidth = 0.5f * aspectRatio;
        float halfHeight = 0.5f;

        float positions[] = {
            -halfWidth, -halfHeight,
            halfWidth, -halfHeight,
            halfWidth, halfHeight,
            -halfWidth, halfHeight};

        float uvs[] = {
            u0, v0,
            u1, v0,
            u1, v1,
            u0, v1};

        StandardMesh mesh(4, GL_TRIANGLE_FAN);
        mesh.setNbElt(4);
        mesh.addOneBuffer(0, 2, positions, "position", true);
        mesh.addOneBuffer(2, 2, uvs, "texcoord", true);

        return mesh;
    }

    void updateUVs(StandardMesh &mesh, int col, int row, float tileWidth, float tileHeight, float atlasWidth, float atlasHeight)
    {
        float u0 = (col * tileWidth) / atlasWidth;
        float v0 = 1.0f - ((row + 1) * tileHeight / atlasHeight);
        float u1 = u0 + (tileWidth / atlasWidth);
        float v1 = v0 + (tileHeight / atlasHeight);

        float uvs[] = {
            u0, v0, // bottom-left
            u1, v0, // bottom-right
            u1, v1, // top-right
            u0, v1  // top-left
        };

        mesh.updateBuffer(2, uvs, 8);
    }

    void initTexture(GLBI_Texture &textureAtlas, std::string const atlasName, std::string const ext)
    {
        glfwMakeContextCurrent(getGame()->window);

        int w, h, c;
        stbi_set_flip_vertically_on_load(true);
        std::string imagePath{"../../assets/images/" + atlasName + "." + ext};
        unsigned char *imgData{stbi_load(imagePath.c_str(), &w, &h, &c, ext == "jpg" ? 0 : STBI_rgb_alpha)};
        if (!imgData)
        {
            std::cerr << "[initTexture] Failed to load image '" << imagePath << "': " << stbi_failure_reason() << std::endl;
            throw std::runtime_error("initTexture: Echec du chargement de l'image.");
        }
        textureAtlas.createTexture();
        textureAtlas.attachTexture();
        textureAtlas.setParameters(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        textureAtlas.setParameters(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        textureAtlas.setParameters(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        textureAtlas.setParameters(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        textureAtlas.loadImage(w, h, c, imgData);

        /// DETACH TEXTURE

        textureAtlas.detachTexture();
        stbi_image_free(imgData);
        std::cout << "[initTexture] Image '" << imagePath << "' loaded (" << w << "x" << h << ", " << c << " canaux)." << std::endl;
    }
}
