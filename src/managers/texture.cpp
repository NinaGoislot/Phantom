#include <vector>
#include <cmath>
#include "glbasimac/glbi_texture.hpp"
#include "tools/shaders.hpp"
#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "tools/stb_image.h"

using namespace glbasimac;

namespace Texturing
{
    StandardMesh createPlayerTileMesh(int frameIndex, float tileWidth, float tileHeight, float atlasWidth, float atlasHeight)
    {
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
            u0, v0, // bottom-left
            u1, v0, // bottom-right
            u1, v1, // top-right
            u0, v1  // top-left
        };

        StandardMesh mesh(4, GL_TRIANGLE_FAN);
        mesh.setNbElt(4);
        mesh.addOneBuffer(0, 2, positions, "position", true);
        mesh.addOneBuffer(2, 2, uvs, "texcoord", true);
        return mesh;
    }

    StandardMesh createAutoTiledMesh(float uvSize)
    {
        // Coordonnées des sommets (x, y)
        float positions[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f};
        // Coordonnées UV (u, v)
        float uvs[] = {
            0, 0,
            uvSize, 0,
            uvSize, uvSize,
            0, uvSize};

        StandardMesh mesh(4, GL_TRIANGLE_FAN);
        mesh.setNbElt(4);
        // Attrib location 0 pour position, 2 floats
        mesh.addOneBuffer(0, 2, positions, "position", true);
        // Attrib location 2 pour UV, 2 floats
        mesh.addOneBuffer(2, 2, uvs, "texcoord", true);
        return mesh;
    }

    void initTexture(GLBI_Texture &textureAtlas, std::string const atlasName, std::string const ext)
    {
        int w, h, c;
        stbi_set_flip_vertically_on_load(true);
        std::string imagePath{"../../assets/images/" + atlasName + "." + ext};
        unsigned char *imgData{stbi_load(imagePath.c_str(), &w, &h, &c, ext == "jpg" ? 0 : STBI_rgb_alpha)};
        if (!imgData)
        {
            std::cout << "Failed to load image: " << stbi_failure_reason() << std::endl;
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
    }
}
