#include "patricia.hpp"
#include "map/pathfinding.hpp"

glm::ivec2 Patricia::convertToGridCoordinates(glm::vec2 position)
{
    glm::vec2 adjustedPos = position + glm::vec2(MAP_WIDTH / 2, MAP_HEIGHT / 2);
    glm::ivec2 entityPos = glm::ivec2(glm::round(adjustedPos));
    return entityPos;
}

void Patricia::checkIfPlayerIsTouched(const glm::vec2 &position)
{
    auto &grid = getGrid();
    glm::ivec2 posGrid = convertToGridCoordinates(position);

    if (grid[posGrid.y][posGrid.x].distance < 2)
    {
        auto player = getPlayer();
        player->takeDamage(1);
    }
}


void Patricia::init()
{
    try
    {
        Texturing::initTexture(patriciaAtlas, "patricia", "png");
    }
    catch (const std::exception &e)
    {
        std::cerr << "[Patricia::init] Erreur lors de l'initialisation de la texture : " << e.what() << std::endl;
        return;
    }

    square = Texturing::createPlayerTileMesh(0);
    if (!square.createVAO())
    {
        std::cerr << "[Patricia::init] Echec de la création du VAO pour le villain." << std::endl;
        return;
    }

    speed = 3.0f;
    viewRange = 15;

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

    std::cout << "[Patricia::init] Patricia initialized" << std::endl;
}

void Patricia::setFrame(int frameIndex)
{
    currentFrame = frameIndex;
    Texturing::updateUVs(square, frameIndex, 0, 16.0f, 32.0f, 256.0f, 32.0f);
}

void Patricia::updateAnimatedFrame()
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

void Patricia::move(glm::vec2 direction)
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

void Patricia::anim_up()
{
    frameDirection = 4;
    updateAnimatedFrame();
}

void Patricia::anim_down()
{
    frameDirection = 0;
    updateAnimatedFrame();
}

void Patricia::anim_left()
{
    frameDirection = 12;
    updateAnimatedFrame();
}

void Patricia::anim_right()
{
    frameDirection = 8;
    updateAnimatedFrame();
}

void Patricia::update()
{
    auto &grid = getGrid();
    glm::vec2 gridPos = convertToGridCoordinates(position);

    Cell &cell = grid[gridPos.y][gridPos.x];

    glm::vec2 dir = glm::vec2(cell.direction);

    move(dir);

    checkIfPlayerIsTouched(position);
}

void Patricia::draw(glbasimac::GLBI_Engine &engine)
{
    engine.activateTexturing(true);
    patriciaAtlas.attachTexture();

    engine.mvMatrixStack.pushMatrix();
    engine.mvMatrixStack.addTranslation(Vector3D(position.x, position.y, 0));
    // engine.mvMatrixStack.addTranslation(Vector3D(2., 6., 0));
    engine.setFlatColor(1.0f, 0.0f, 0.0f); // carré rouge
    engine.updateMvMatrix();
    square.draw();
    engine.mvMatrixStack.popMatrix();

    patriciaAtlas.detachTexture();
    engine.activateTexturing(false);
}