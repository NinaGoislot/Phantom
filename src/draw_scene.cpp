#include "draw_scene.hpp"
#include "GLFW/glfw3.h"
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <cmath>

// to add
#include "map.hpp"
#include "text.hpp"

using namespace glbasimac;

GLBI_Engine myEngine;


// OpenGL Shapes
GLBI_Convex_2D_Shape carre;
GLBI_Convex_2D_Shape triangle;
GLBI_Convex_2D_Shape cercle;
GLBI_Convex_2D_Shape trapeze;

static bool minusAngleActivated = false;

// to add
void drawOneTile(int &x, int &y, float color)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(static_cast<float>(x), static_cast<float>(y), 0.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(color, color, color);
    carre.drawShape();
    myEngine.mvMatrixStack.popMatrix();
}

// to add
void drawMap()
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addHomothety(0.2);
    myEngine.updateMvMatrix();
    carre.drawShape();
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-MAP_WIDTH / 2, -MAP_HEIGHT / 2, 0.0));
    myEngine.updateMvMatrix();
    for (int h{0}; h < MAP_WIDTH; h++)
    {
        for (int w{0}; w < MAP_HEIGHT; w++)
        {
            if (isAlive(w, h))
            {
                drawOneTile(w, h, 1.0);
            }
            else
            {
                drawOneTile(w, h, 0.0);
            }
        }
    }
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.popMatrix();
}


void initScene()
{
    textInit();

    // to add
    generateMap(10);
    playerSpawner(5);

    std::vector<float> originCoord{1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0}; // manually put coord here to match the first arm not ideal
    carre.initShape(originCoord);
    carre.changeNature(GL_TRIANGLE_FAN);
}

void renderScene()
{
    myEngine.switchToFlatShading();
    drawMap();
    textDraw("Lorem ipsum", 500, 100, SimpleText::CENTER, SimpleText::SIZE_16);
}