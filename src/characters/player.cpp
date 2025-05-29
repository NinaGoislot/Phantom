#include "player.hpp"

void Player::init()
{
    std::vector<float> squareCoords = {
        -0.5f * size.x, 0.5f * size.y,
        -0.5f * size.x, -0.5f * size.y,
        0.5f * size.x, -0.5f * size.y,
        0.5f * size.x, 0.5f * size.y};

    square.initShape(squareCoords);
    square.changeNature(GL_TRIANGLE_FAN);
}

void Player::move(glm::vec2 direction)
{
    // if (glm::length(direction) > 0.0f)
    // {
    //     direction = glm::normalize(direction);
    // }
    position += direction * speed * static_cast<float>(get_loop_time().getDeltaTime());
}

void Player::move_top()
{
    move(glm::vec2(0, 1));
}
void Player::move_bottom()
{
    move(glm::vec2(0, -1));
}
void Player::move_left()
{
    move(glm::vec2(-1, 0));
}
void Player::move_right()
{
    move(glm::vec2(1, 0));
}

void Player::draw(glbasimac::GLBI_Engine &engine)
{
    // For now, it's juste a square
    engine.mvMatrixStack.pushMatrix();
    engine.mvMatrixStack.addTranslation(Vector3D(position.x, position.y, 0));
    // engine.mvMatrixStack.addTranslation(Vector3D(2., 6., 0));
    engine.setFlatColor(1.0f, 0.0f, 0.0f); // carré rouge
    engine.updateMvMatrix();
    square.drawShape();
    engine.mvMatrixStack.popMatrix();
}