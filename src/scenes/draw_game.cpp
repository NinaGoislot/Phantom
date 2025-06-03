//Opengl
#include "glad/glad.h" // DOIT être le premier include lié à OpenGL
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include "glbasimac/glbi_texture.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/shaders.hpp"
#include "tools/basic_mesh.hpp"
#include "tools/stb_image.h"
#include "glbasimac/glbi_engine.hpp"
using namespace glbasimac;

//External files
#include "controls/controls.hpp"
#include "scenes/draw_game.hpp"
#include "managers/menu.hpp"

//External libs
#include <vector>
#include <cmath>


GLBI_Engine myEngine;

static StandardMesh createAutoTiledMesh()
{
    // Coordonnées des sommets (x, y)
    static float positions[] = {
        -0.6f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f};
    // Coordonnées UV (u, v)
    static float uvs[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f};

    StandardMesh mesh(4, GL_TRIANGLE_FAN);
    mesh.setNbElt(4);
    // Attrib location 0 pour position, 2 floats
    mesh.addOneBuffer(0, 2, positions, "position", true);
    // Attrib location 1 pour UV, 2 floats
    mesh.addOneBuffer(2, 2, uvs, "texcoord", true);
    mesh.addOneBuffer(1, 2, uvs, "uvs", true);
    mesh.createVAO();
    return mesh;
}

// OpenGL Shapes
// GLBI_Convex_2D_Shape carre;
StandardMesh square;
StandardMesh* rectangle;
GLBI_Convex_2D_Shape triangle;
GLBI_Convex_2D_Shape cercle;
GLBI_Convex_2D_Shape trapeze;

// Textures 
GLBI_Texture myTexture;

static bool minusAngleActivated = false;

void drawSquare() {
    myEngine.activateTexturing(true);
	myTexture.attachTexture();
    myEngine.setFlatColor(1.0,1.0,1.0);

    myEngine.mvMatrixStack.pushMatrix();
        square.draw();
    myEngine.mvMatrixStack.popMatrix();

    myTexture.detachTexture();
	myEngine.activateTexturing(false);
}

void DrawGame::init()
{
  
    int w, h, c;
    stbi_set_flip_vertically_on_load(true);  
	unsigned char* imgData {stbi_load("../../assets/images/poulpile.jpg", &w, &h, &c, 0)};
    if (!imgData) {
        std::cout << "Failed to load image: " << stbi_failure_reason() << std::endl;
    }
    myTexture.createTexture();
	myTexture.attachTexture();
    myTexture.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	myTexture.loadImage(w, h, c, imgData);

    square = createAutoTiledMesh();
    square.createVAO();

    std::vector<float> squareLoc{1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0};

    std::vector<float> circleLoc{};
    int nbCirclePoints{100};
    float circleRadius{1};
    float dbPi{2.0 * M_PI};
    float theta{};
    float xCircle{};
    float yCircle{};

    for (size_t i = 0; i < nbCirclePoints; i++)
    {
        theta = (dbPi * i) / nbCirclePoints;
        xCircle = circleRadius * cos(theta);
        yCircle = circleRadius * sin(theta);

        circleLoc.push_back(xCircle);
        circleLoc.push_back(yCircle);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    myTexture.detachTexture();
	stbi_image_free(imgData);
}

void DrawGame::render(const Game& game)
{
    // switch to opengl shaders
    myEngine.switchToFlatShading();


    myEngine.mvMatrixStack.pushMatrix();

    const float spacing = 1.1f;
    const int rows = 5;
    const int cols = 5;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation({j * spacing, i * spacing, 0.0f});
            myEngine.updateMvMatrix();
            drawSquare();
            myEngine.mvMatrixStack.popMatrix();
        }
    }

    myEngine.mvMatrixStack.popMatrix();
    game.player->draw(myEngine);

    displayMenu(0); // Display the menu with item 0
}


//voilà comment j'ai appelé mes fonctions tah l'époque

// void drawOneTile(int &x, int &y, float color)
// {
//     myEngine.mvMatrixStack.pushMatrix();
//     myEngine.mvMatrixStack.addTranslation(Vector3D(static_cast<float>(x), static_cast<float>(y), 0.0));
//     myEngine.updateMvMatrix();
//     myEngine.setFlatColor(color, color, color);
//     carre.drawShape();
//     myEngine.mvMatrixStack.popMatrix();
// }

// void drawMap()
// {
//     myEngine.mvMatrixStack.pushMatrix();
//     myEngine.mvMatrixStack.addHomothety(0.2);
//     myEngine.updateMvMatrix();
//     carre.drawShape();
//     myEngine.mvMatrixStack.pushMatrix();
//     myEngine.mvMatrixStack.addTranslation(Vector3D(-MAP_WIDTH / 2, -MAP_HEIGHT / 2, 0.0));
//     myEngine.updateMvMatrix();
//     for (int h{0}; h < MAP_WIDTH; h++)
//     {
//         for (int w{0}; w < MAP_HEIGHT; w++)
//         {
//             if (isAlive(w, h))
//             {
//                 drawOneTile(w, h, 1.0);
//             }
//             else
//             {
//                 drawOneTile(w, h, 0.0);
//             }
//         }
//     }
//     myEngine.mvMatrixStack.popMatrix();
//     myEngine.mvMatrixStack.popMatrix();
// }

// void initScene()
// {
//     textInit();

//     // to add
//     generateMap(10);
//     playerSpawner(5);

//     std::vector<float> originCoord{1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0}; // manually put coord here to match the first arm not ideal
//     carre.initShape(originCoord);
//     carre.changeNature(GL_TRIANGLE_FAN);
// }

// void renderScene()
// {
//     myEngine.switchToFlatShading();
//     drawMap();
//     displayMenu(0); // Display the menu with item 0
//     // textDraw("Lorem ipsum", width, height, SimpleText::CENTER, SimpleText::SIZE_16);
// }