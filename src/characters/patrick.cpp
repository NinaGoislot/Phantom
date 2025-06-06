#include "patrick.hpp"
#include "map/pathfinding.hpp"

glm::ivec2 Patrick::convertToGridCoordinates(glm::vec2 position)
{
    glm::vec2 adjustedPos = position + glm::vec2(MAP_WIDTH / 2, MAP_HEIGHT / 2);
    glm::ivec2 entityPos = glm::ivec2(glm::round(adjustedPos));
    return entityPos;
}

void Patrick::checkIfPlayerIsTouched(const glm::vec2 &position)
{
    auto &grid = getGrid();
    glm::ivec2 posGrid = convertToGridCoordinates(position);

    if (grid[posGrid.y][posGrid.x].distance < 2)
    {
        auto player = getPlayer();
        player->takeDamage(1);
    }
}

void Patrick::init()
{
    try
    {
        Texturing::initTexture(patrickAtlas, "patrick", "png");
    }
    catch (const std::exception &e)
    {
        std::cerr << "[Patrick::init] Erreur lors de l'initialisation de la texture : " << e.what() << std::endl;
        return;
    }

    square = Texturing::createPlayerTileMesh(0);
    if (!square.createVAO())
    {
        std::cerr << "[Patrick::init] Echec de la création du VAO pour le villain." << std::endl;
        return;
    }

    speed = 4.0f;
    viewRange = 20;

    // random spaww
    const std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> &grid = getGrid();
    const int MIN_DISTANCE_SPAWN = MAX_DISTANCE;

    srand(static_cast<unsigned>(time(nullptr))); // seed

    bool canSpawn = false;
    while (!canSpawn)
    {
        int x = rand() % MAP_WIDTH;
        int y = rand() % MAP_HEIGHT;

        glm::ivec2 entityPos = convertToGridCoordinates(glm::vec2{x, y});

        if (isInsideGrid(glm::vec2{entityPos.x, entityPos.y}) && grid[entityPos.y][entityPos.x].walkable && grid[entityPos.y][entityPos.x].distance >= MIN_DISTANCE_SPAWN)
        {
            position = {x, y};
            canSpawn = true;
        }
    }

    std::cout << "[Patrick::init] Patricia initialized" << std::endl;
}

void Patrick::setFrame(int frameIndex)
{
    currentFrame = frameIndex;
    Texturing::updateUVs(square, frameIndex, 0, 16.0f, 32.0f, 256.0f, 32.0f);
}

void Patrick::updateAnimatedFrame()
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

void Patrick::move(glm::vec2 direction)
{
    if (direction.x == 1)
        anim_right();
    if (direction.y == 1)
        anim_up();
    if (direction.y == -1)
        anim_down();
    if (direction.x == -1)
        anim_left();
    position += direction * speed * static_cast<float>(get_loop_time().getDeltaTime());
}

void Patrick::anim_up()
{
    frameDirection = 4;
    updateAnimatedFrame();
}

void Patrick::anim_down()
{
    frameDirection = 0;
    updateAnimatedFrame();
}

void Patrick::anim_left()
{
    frameDirection = 12;
    updateAnimatedFrame();
}

void Patrick::anim_right()
{
    frameDirection = 8;
    updateAnimatedFrame();
}

void Patrick::update()
{
    if (getPlayer()->isMoving)
    {
        generateFlowFieldExtended(viewRange);
        auto &grid = getGrid();
        glm::vec2 gridPos = convertToGridCoordinates(position);

        Cell &cell = grid[gridPos.y][gridPos.x];

        glm::vec2 dir = glm::vec2(cell.direction);

        move(dir);

        checkIfPlayerIsTouched(position);
    }
    else
    {
        // Pourcentage de change de pas bouger
        int randomMoveChance = rand() % 10; // 0, 1, or 2
        if (randomMoveChance == 1)
        {
            // move aleatoirement
            glm::vec2 randomDirection = glm::vec2(rand() % 3 - 1, rand() % 3 - 1); // -1, 0, or 1 for both x and y
            move(randomDirection);
        }
    }
}

void Patrick::draw(glbasimac::GLBI_Engine &engine)
{
    engine.activateTexturing(true);
    patrickAtlas.attachTexture();

    engine.mvMatrixStack.pushMatrix();
    engine.mvMatrixStack.addTranslation(Vector3D(position.x, position.y, 0));
    // engine.mvMatrixStack.addTranslation(Vector3D(2., 6., 0));
    engine.setFlatColor(1.0f, 0.0f, 0.0f); // carré rouge
    engine.updateMvMatrix();
    square.draw();
    engine.mvMatrixStack.popMatrix();

    patrickAtlas.detachTexture();
    engine.activateTexturing(false);
}