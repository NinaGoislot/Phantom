#include "scenes/scene.hpp"
#include "managers/gameManager.hpp"  // ici, la déclaration de myEngine est bien incluse

void Scene::drawBackground(glbasimac::GLBI_Texture &Texture, STP3D::StandardMesh &Tile)
{
    myEngine.activateTexturing(true);
    Texture.attachTexture();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0, 0));
    myEngine.mvMatrixStack.addHomothety(25.0);
    myEngine.setFlatColor(1.0f, 0.0f, 0.0f);
    myEngine.updateMvMatrix();
    Tile.draw();
    myEngine.mvMatrixStack.popMatrix();

    Texture.detachTexture();
    myEngine.activateTexturing(false);
}

void Scene::drawButton(glbasimac::GLBI_Texture &Texture, STP3D::StandardMesh &Tile, float BUTTON_OFFSET_X, float BUTTON_OFFSET_Y)
{
    myEngine.activateTexturing(true);
    Texture.attachTexture();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(BUTTON_OFFSET_X, BUTTON_OFFSET_Y, 0));
    myEngine.mvMatrixStack.addHomothety(1.5);
    myEngine.setFlatColor(1.0f, 0.0f, 0.0f);
    myEngine.updateMvMatrix();
    Tile.draw();
    myEngine.mvMatrixStack.popMatrix();

    Texture.detachTexture();
    myEngine.activateTexturing(false);
}