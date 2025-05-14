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

using namespace glbasimac;

GLBI_Engine myEngine;

// OpenGL Shapes
GLBI_Convex_2D_Shape carre;
GLBI_Convex_2D_Shape triangle;
GLBI_Convex_2D_Shape cercle;
GLBI_Convex_2D_Shape trapeze;

static bool minusAngleActivated = false;

//to add
void drawOneTile(int& x, int& y, float color)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(static_cast<float>(x), static_cast<float>(y), 0.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(color, color, color);
    carre.drawShape();
    myEngine.mvMatrixStack.popMatrix();
}

//to add
void drawMap()
{
    carre.drawShape();
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-MAP_WIDTH/2, -MAP_HEIGHT/2, 0.0));
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
}

void initScene()
{
    // std::vector<float> squareLoc{1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0};

    // std::vector<float> circleLoc{};
    // int nbCirclePoints{100};
    // float circleRadius{1};
    // float dbPi{2.0 * M_PI};
    // float theta{};
    // float xCircle{};
    // float yCircle{};

    // for (size_t i = 0; i < nbCirclePoints; i++)
    // {
    //     theta = (dbPi * i) / nbCirclePoints;
    //     xCircle = circleRadius * cos(theta);
    //     yCircle = circleRadius * sin(theta);

    //     circleLoc.push_back(xCircle);
    //     circleLoc.push_back(yCircle);
    // }

    // std::vector<float> triangleLoc{-0.5, -0.5, 0.5, -0.5, 0.0, 0.5};
    // std::vector<float> colors{1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0};

    // std::vector<float> trapezeLoc{0.0, 2.0, 0.0, -2.0, 6.0, -1.0, 6.0, 1.0}; // manually put coord here to match the first arm not ideal
    // carre.initShape(squareLoc);
    // triangle.initShape(triangleLoc);
    // cercle.initShape(circleLoc);
    // trapeze.initShape(trapezeLoc);
    // /////////////////////////////////////////////////////////////////////////////////////

    std::vector<float> originCoord {1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0}; // manually put coord here to match the first arm not ideal
    carre.initShape(originCoord);
    carre.changeNature(GL_TRIANGLE_FAN);
}

void renderScene()
{
    drawMap();
}