#include "villain.hpp"
#include "map/pathfinding.hpp"

void Villain::init()
{
position = glm::vec2(10.0f, 10.0f);
}

void Villain::move(glm::vec2 direction)
{
    std::cout << "[Villain] Moving in direction: (" << direction.x << ", " << direction.y << ")" << std::endl;
    position += direction * speed * static_cast<float>(get_loop_time().getDeltaTime());
}

void Villain::update()
{
    glm::vec2 playerPos = getPlayer()->getPosition();
    float maxDistance = static_cast<float>(GL_VIEW_SIZE);

    // Si joueur trop loin => ne bouge pas
    if (glm::distance2(position, playerPos) > maxDistance * maxDistance)
    {
        return;
    }

    glm::ivec2 gridPos = position;
    // if (!isInsideGrid(gridPos)){
    //     return;
    // }

    glm::vec2 dir = getGrid()[gridPos.y][gridPos.x].direction;

    if (dir != glm::vec2(0))
    {
        // move(dir);
    }
}

void Villain::draw(glbasimac::GLBI_Engine& engine) {
        engine.activateTexturing(false);
       engine.activateTexturing(false); // pas de texture
    engine.setFlatColor(1.0f, 0.0f, 0.0f); // rouge

    engine.mvMatrixStack.pushMatrix();
    engine.mvMatrixStack.addTranslation(Vector3D(position.x, position.y, 0));
    engine.mvMatrixStack.addHomothety(Vector3D(1.0f, 1.0f, 1.0f)); // taille du carré
    engine.updateMvMatrix();

    // Carré en OpenGL immédiat pour debug (GL_QUADS n'est plus supporté en core, mais ici c'est à titre simple)
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(-0.5f, -0.5f); // bas gauche
        glVertex2f( 0.5f, -0.5f); // bas droit
        glVertex2f( 0.5f,  0.5f); // haut droit
        glVertex2f(-0.5f,  0.5f); // haut gauche
    glEnd();

    engine.mvMatrixStack.popMatrix();
    engine.setFlatColor(1.0f, 1.0f, 1.0f); // reset couleur
    }