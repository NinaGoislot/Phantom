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

    void initTexture(GLBI_Texture &textureAtlas)
    {
        int w, h, c;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *imgData{stbi_load("../../assets/images/poulpile.jpg", &w, &h, &c, 0)}; // texture atlas
        if (!imgData)
        {
            std::cout << "Failed to load image: " << stbi_failure_reason() << std::endl;
        }
        textureAtlas.createTexture();
        textureAtlas.attachTexture();
        textureAtlas.setParameters(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        textureAtlas.setParameters(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        textureAtlas.setParameters(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        textureAtlas.loadImage(w, h, c, imgData);

        /// DETACH TEXTURE

        textureAtlas.detachTexture();
        stbi_image_free(imgData);
    }
}
