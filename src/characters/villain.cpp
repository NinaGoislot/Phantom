#include "villain.hpp"
#include "map/pathfinding.hpp"

void Villain::init()
{
    position = glm::vec2(10.0f, 10.0f);
    speed = 1.0f;
}

void Villain::move(glm::vec2 direction)
{
    // std::cout << "[Villain] Moving in direction: (" << direction.x << ", " << direction.y << ")" << std::endl;
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

    move(dir);
}

void Villain::draw(glbasimac::GLBI_Engine &engine)
{

}