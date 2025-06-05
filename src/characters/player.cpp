#include "player.hpp"
#include "managers/text.hpp"
#include "managers/gameManager.hpp"

void Player::init()
{
    try
    {
        Texturing::initTexture(playerAtlas, "Player", "png");
    }
    catch (const std::exception &e)
    {
        std::cerr << "[Player::init] Erreur lors de l'initialisation de la texture : " << e.what() << std::endl;
        return;
    }

    square = Texturing::createPlayerTileMesh(0);
    if (!square.createVAO())
    {
        std::cerr << "[Player::init] Echec de la création du VAO pour le joueur." << std::endl;
        return;
    }

    std::cout << "[Player::init] Player initialized" << std::endl;
}

void Player::setFrame(int frameIndex)
{
    currentFrame = frameIndex;
    Texturing::updateUVs(square, frameIndex, 0, 16.0f, 32.0f, 256.0f, 32.0f);
}

void Player::updateAnimatedFrame()
{
    if (frameDirection != lastFrameDirection)
    {
        animationStep = 0;
        animationTimer = 0.0f;
        lastFrameDirection = frameDirection;
        setFrame(frameDirection); // Immediately show first frame of new direction
    }

    animationTimer += static_cast<float>(get_loop_time().getDeltaTime());

    if (animationTimer >= frameDuration)
    {
        animationTimer = 0.0f;                   // reset timer
        animationStep = (animationStep + 1) % 4; // loop through frames
        currentFrame = frameDirection + animationStep;
        setFrame(currentFrame);
    }
}

void Player::move(glm::vec2 direction)
{
    // if (glm::length(direction) > 0.0f)
    // {
    //     direction = glm::normalize(direction);
    // }
    position += direction * speed * static_cast<float>(get_loop_time().getDeltaTime());
}

void Player::anim_up()
{
    frameDirection = 4;
    updateAnimatedFrame();
}

void Player::anim_down()
{
    frameDirection = 0;
    updateAnimatedFrame();
}

void Player::anim_left()
{
    frameDirection = 12;
    updateAnimatedFrame();
}

void Player::anim_right()
{
    frameDirection = 8;
    updateAnimatedFrame();
}

void Player::move_up()
{
    move(glm::vec2(0, 1));
    anim_up();
}
void Player::move_down()
{
    move(glm::vec2(0, -1));
    anim_down();
}
void Player::move_left()
{
    move(glm::vec2(-1, 0));
    anim_left();
}
void Player::move_right()
{
    move(glm::vec2(1, 0));
    anim_right();
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

glm::vec2 Player::getPosition()
{
    return position;
}

void Player::takeDamage(int damage)
{
    if (!godMode)
    {
        life -= damage;
        if (life <= 0)
        {
            std::cout << "[Player] You died!" << std::endl;
            launchLooseScene();
        }
        godMode = true;
        damageCooldownTimer = DAMAGE_COOLDOWN;

        // textDraw("OUCH! it hurts!",
        //          400, 400, SimpleText::Color::RED,
        //          SimpleText::Alignment::CENTER, SimpleText::SIZE_16, true);

        std::cout << "[Player::takeDamage] " << damage << " damage(s) to player" << std::endl;
    }
    else
    {
        std::cout << "[Player::takeDamage] Player is in god mode, no damage taken." << std::endl;
        std::cout << "[Player::takeDamage] Cooldown restant : " << damageCooldownTimer << std::endl;
    }
}

int Player::getLife()
{
    return life;
}