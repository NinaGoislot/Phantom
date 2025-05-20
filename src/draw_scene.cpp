#include "draw_scene.hpp"
#include "GLFW/glfw3.h"
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <cmath>
#include "glbasimac/glbi_texture.hpp"
#include "tools/shaders.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "tools/stb_image.h"

using namespace glbasimac;

GLBI_Engine myEngine;

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

// OpenGL Shapes
// GLBI_Convex_2D_Shape carre;
StandardMesh square;
StandardMesh square2;

// Textures 
GLBI_Texture textureAtlas;

bool minusAngleActivated = false;

void drawTile(const StandardMesh& textureTile) {
    myEngine.activateTexturing(true);
	textureAtlas.attachTexture();
    myEngine.setFlatColor(1.0,1.0,1.0);

    myEngine.mvMatrixStack.pushMatrix();
        textureTile.draw();
    myEngine.mvMatrixStack.popMatrix();

    textureAtlas.detachTexture();
	myEngine.activateTexturing(false);
}

void initScene()
{
  
    int w, h, c;
    stbi_set_flip_vertically_on_load(true);  
	unsigned char* imgData {stbi_load("../../assets/images/poulpile.jpg", &w, &h, &c, 0)}; // texture atlas
    if (!imgData) {
        std::cout << "Failed to load image: " << stbi_failure_reason() << std::endl;
    }
    textureAtlas.createTexture();
	textureAtlas.attachTexture();
    textureAtlas.setParameters(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    textureAtlas.setParameters(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    textureAtlas.setParameters(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	textureAtlas.loadImage(w, h, c, imgData);

    // Deal with uv position TODO add like a uv function to generate

    // TODO : Change uv during animation to create animation
    // add animator manager

    square = createAutoTiledMesh(0.5f);
    square.createVAO();
    square2 = createAutoTiledMesh(1.0f);
    square2.createVAO();

    /////////////////////////////////////////////////////////////////////////////////////
    textureAtlas.detachTexture();
	stbi_image_free(imgData);
}

void renderScene(const Game& game)
{
    myEngine.mvMatrixStack.pushMatrix();

    const float spacing = 1.0f;
    const int rows = 5;
    const int cols = 5;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation({j * spacing, i * spacing, 0.0f});
            myEngine.updateMvMatrix();
            if ((i+j) % 2) // if broken like add condition to change the textures // add randomness
            {
                drawTile(square);
            } else {
                drawTile(square2);
            }
            
            myEngine.mvMatrixStack.popMatrix();
        }
    }

    myEngine.mvMatrixStack.popMatrix();

    game.player->draw(myEngine);
}