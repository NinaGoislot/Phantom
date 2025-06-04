#include "player.hpp"

void Player::init()
{
    Texturing::initTexture(playerAtlas, "Player", "png");
    square = Texturing::createPlayerTileMesh(0);
    square.createVAO();
}

void Player::setFrame(int frameIndex)
{
    // square = Texturing::createPlayerTileMesh(frameIndex);
    // square.createVAO();
    currentFrame = frameIndex;
    Texturing::updateUVs(square, frameIndex, 0, 16.0f, 32.0f, 256.0f, 32.0f);

}

void Player::updateAnimatedFrame()
{
    currentFrame = frameDirection + animationStep;
    setFrame(currentFrame);

    animationStep = (animationStep + 1) % 4; 
}


void Player::move(glm::vec2 direction)
{
    // if (glm::length(direction) > 0.0f)
    // {
    //     direction = glm::normalize(direction);
    // }
    position += direction * speed * static_cast<float>(get_loop_time().getDeltaTime());
}

void Player::move_up()
{
    frameDirection = 4;
    updateAnimatedFrame();
    move(glm::vec2(0, 1));
}
void Player::move_down()
{
    frameDirection = 0;
    updateAnimatedFrame();
    move(glm::vec2(0, -1));
}
void Player::move_left()
{
    frameDirection = 12;
    updateAnimatedFrame();
    move(glm::vec2(-1, 0));
}
void Player::move_right()
{
    frameDirection = 8;
    updateAnimatedFrame();
    move(glm::vec2(1, 0));
}

void Player::draw(glbasimac::GLBI_Engine &engine)
{
    engine.activateTexturing(true);
    playerAtlas.attachTexture();

    engine.mvMatrixStack.pushMatrix();
    engine.mvMatrixStack.addTranslation(Vector3D(position.x, position.y, 0));
    // engine.mvMatrixStack.addTranslation(Vector3D(2., 6., 0));
    engine.setFlatColor(1.0f, 0.0f, 0.0f); // carré rouge
    engine.updateMvMatrix();
    square.draw();
    engine.mvMatrixStack.popMatrix();

    playerAtlas.detachTexture();
    engine.activateTexturing(false);
}