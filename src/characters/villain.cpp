#include "villain.hpp"
#include "map/pathfinding.hpp"

void Villain::init()
{
position = glm::vec2(10.0f, 10.0f);
speed = 1.0f;

try
    {
        Texturing::initTexture(villainAtlas, "villain", "png");
    }
    catch (const std::exception &e)
    {
        std::cerr << "[Villain::init] Erreur lors de l'initialisation de la texture : " << e.what() << std::endl;
        return;
    }

    square = Texturing::createPlayerTileMesh(0);
    if (!square.createVAO())
    {
        std::cerr << "[Villain::init] Echec de la création du VAO pour le villain." << std::endl;
        return;
    }

    std::cout << "[Villain::init] Villain initialized" << std::endl;
    position = glm::vec2(10.0f, 10.0f);
    speed = 1.0f;
}

void Villain::setFrame(int frameIndex)
{
    currentFrame = frameIndex;
    Texturing::updateUVs(square, frameIndex, 0, 16.0f, 32.0f, 256.0f, 32.0f);
}

void Villain::updateAnimatedFrame()
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

void Villain::move(glm::vec2 direction)
{
    // std::cout << "[Villain] Moving in direction: (" << direction.x << ", " << direction.y << ")" << std::endl;
    position += direction * speed * static_cast<float>(get_loop_time().getDeltaTime());
}

void Villain::anim_up()
{
    frameDirection = 4;
    updateAnimatedFrame();
}

void Villain::anim_down()
{
    frameDirection = 0;
    updateAnimatedFrame();
}

void Villain::anim_left()
{
    frameDirection = 12;
    updateAnimatedFrame();
}

void Villain::anim_right()
{
    frameDirection = 8;
    updateAnimatedFrame();
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

void Villain::draw(glbasimac::GLBI_Engine& engine) {
    engine.activateTexturing(true);
    villainAtlas.attachTexture();

    engine.mvMatrixStack.pushMatrix();
    engine.mvMatrixStack.addTranslation(Vector3D(position.x, position.y, 0));
    // engine.mvMatrixStack.addTranslation(Vector3D(2., 6., 0));
    engine.setFlatColor(1.0f, 0.0f, 0.0f); // carré rouge
    engine.updateMvMatrix();
    square.draw();
    engine.mvMatrixStack.popMatrix();

    villainAtlas.detachTexture();
    engine.activateTexturing(false);
    }