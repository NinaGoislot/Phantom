#include "grid.hpp"
#include "managers/gameManager.hpp"

//-----------------------------------------------------------------------------------------
//------------------------------------- DECLARATIONS --------------------------------------
//-----------------------------------------------------------------------------------------

// creation d'un objet pour dire si la case est en vie ou pas
const bool ALIVE{true};
const bool DEAD{false};

//-----------------------------------------------------------------------------------------
//----------------------------------------- DATAS -----------------------------------------
//-----------------------------------------------------------------------------------------

// creation d'une probabilite de vie pour la generation de la map
// ----- 58 est une bonne valeur ------
const int ALIVE_PROBABILITY = 58;

//-----------------------------------------------------------------------------------------
//------------------------------------- FUNCTIONS -----------------------------------------
//-----------------------------------------------------------------------------------------

void initializeMap(std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> &grid)
{
    // creation d'une seed pour la generation de la map
    int seed = time(NULL);
    // srand(seed) permet de generer une seed aleatoire
    srand(seed);

    // on initialise la map avec des cases mortes
    for (int h{0}; h < MAP_HEIGHT; h++)
    {
        for (int w{0}; w < MAP_WIDTH; w++)
        {
            if (rand() % 100 > ALIVE_PROBABILITY)
            {
                grid[h][w].walkable = DEAD;
            }
            else
            {
                grid[h][w].walkable = ALIVE;
            }
        }
    }
}

// fonction qui genere le spawn du joueur (le spawn est un carré de taille size)
void playerSpawner(int size, std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> &map)
{
    int x = MAP_WIDTH / 2;
    int y = MAP_HEIGHT / 2;

    for (int h{y - size + 1}; h < y + size; h++)
    {
        for (int w{x - size + 1}; w < x + size; w++)
        {
            map[h][w].walkable = ALIVE;
        }
    }
}

// fonction qui calcule le nombre de voisins vivants d'une case
int countAliveNeighbors(int x, int y, std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> &grid)
{
    int count{0};
    // on retire 1 à x et y pour aller dans le coin superieur gauche de la case
    // et on ajoute 2 pour aller dans le coin inferieur droit de la case
    for (int h{y - 1}; h < 2 + y; h++)
    {
        for (int w{x - 1}; w < 2 + x; w++)
        {
            // on verifie que la case est bien dans la map
            if (!(w == x && h == y))
            {
                if (h >= 0 && h < MAP_HEIGHT && w >= 0 && w < MAP_WIDTH)
                {
                    count += grid[h][w].walkable ? 1 : 0; // on ajoute 1 si la case est vivante, sinon on ajoute 0
                }
            }
        }
    }
    return count;
}

// fonction qui genere la map avec un nombre de generations

std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> generateMap(int generations, int spawnSize)
{
    std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> grid;
    initializeMap(grid);


    for (int gen{0}; gen < generations; gen++)
    {
        // on passe par une map temporaire pour ne pas modifier la map en cours
        std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> newGrid;

        for (int h{0}; h < MAP_HEIGHT; h++)
        {
            for (int w{0}; w < MAP_WIDTH; w++)
            {
                int count = countAliveNeighbors(w, h, grid);
                if (grid[h][w].walkable == DEAD && count >= 6)
                    newGrid[h][w].walkable = ALIVE;
                else if (grid[h][w].walkable == ALIVE && count <= 3)
                    newGrid[h][w].walkable = DEAD;
                else
                    newGrid[h][w] = grid[h][w];
            }
        }

        // on copie la map temporaire dans la map principale
        grid = newGrid;
    }
    // displayMap();

    playerSpawner(spawnSize, grid);

    return grid;
}

// fonction qui affiche la map

void displayMap(std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> &map)
{
    for (int h{0}; h < MAP_HEIGHT; h++)
    {
        for (int w{0}; w < MAP_WIDTH; w++)
        {
            if (map[h][w].walkable == ALIVE)
                std::cout << ".";
            else
                std::cout << "#";
        }
        std::cout << std::endl;
    }
}

bool isAlive(int x, int y)
{
    Game *game = getGame();
    return game->grid[y][x].walkable == ALIVE;
}

void digTile(int x, int y)
{
    Game *game = getGame();
    game->grid[y][x].walkable = ALIVE;
}
