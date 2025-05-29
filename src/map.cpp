//-----------------------------------------------------------------------------------------
//------------------------------------- TEST MAP --------------------------------------
//-----------------------------------------------------------------------------------------

#include "map.hpp"

//-----------------------------------------------------------------------------------------
//------------------------------------- DECLARATIONS --------------------------------------
//-----------------------------------------------------------------------------------------

// creation d'un objet pour dire si la case est en vie ou pas
int ALIVE{1};
int DEAD{0};

// creation de la map
int map[MAP_HEIGHT][MAP_WIDTH];

// creation d'une seed pour la generation de la map
int seed = time(NULL);

//-----------------------------------------------------------------------------------------
//----------------------------------------- DATAS -----------------------------------------
//-----------------------------------------------------------------------------------------

// creation d'une probabilite de vie pour la generation de la map
// ----- 58 est une bonne valeur ------
int ALIVE_PROBABILITY = 58;

// nombre de generations
int NB_GENERATIONS = 10;

// taille du spawn du joueur
int SPAWN_SIZE = 5;

//-----------------------------------------------------------------------------------------
//------------------------------------- FUNCTIONS -----------------------------------------
//-----------------------------------------------------------------------------------------

// fonction qui initialise la map

void initializeMap()
{
    // srand(seed) permet de generer une seed aleatoire
    srand(seed);

    // on initialise la map avec des cases mortes
    for (int h{0}; h < MAP_HEIGHT; h++)
    {
        for (int w{0}; w < MAP_WIDTH; w++)
        {
            if (rand() % 100 > ALIVE_PROBABILITY)
            {
                map[h][w] = DEAD;
            }
            else
            {
                map[h][w] = ALIVE;
            }
        }
    }
}

// fonction qui calcule le nombre de voisins vivants d'une case

int countAliveNeighbors(int x, int y)
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
                    count += map[h][w];
                }
            }
        }
    }
    return count;
}

// fonction qui genere la map avec un nombre de generations

void generateMap(int generations = NB_GENERATIONS)
{
    initializeMap();
    std::cout << std::endl;

    for (int gen{0}; gen < generations; gen++)
    {
        // on passe par une map temporaire pour ne pas modifier la map en cours
        int newMap[MAP_HEIGHT][MAP_WIDTH];

        for (int h{0}; h < MAP_HEIGHT; h++)
        {
            for (int w{0}; w < MAP_WIDTH; w++)
            {
                int count = countAliveNeighbors(w, h);
                if (map[h][w] == DEAD && count >= 6)
                    newMap[h][w] = ALIVE;
                else if (map[h][w] == ALIVE && count <= 3)
                    newMap[h][w] = DEAD;
                else
                    newMap[h][w] = map[h][w];
            }
        }

        // on copie la map temporaire dans la map principale
        for (int h = 0; h < MAP_HEIGHT; h++)
        {
            for (int w = 0; w < MAP_WIDTH; w++)
            {
                map[h][w] = newMap[h][w];
            }
        }

    }
        displayMap();
}


// fonction qui affiche la map

void displayMap()
{
    for (int h{0}; h < MAP_HEIGHT; h++)
    {
        for (int w{0}; w < MAP_WIDTH; w++)
        {
            if (map[h][w] == ALIVE)
                std::cout << ".";
            else
                std::cout << "#";
        }
        std::cout << std::endl;
    }
}

// fonction qui genere le spawn du joueur (le spawn est un carré de taille size)
void playerSpawner(int size = SPAWN_SIZE)
{
    int x = MAP_WIDTH / 2;
    int y = MAP_HEIGHT / 2;

    for (int h{y - size + 1}; h < y + size; h++)
    {
        for (int w{x - size + 1}; w < x + size; w++)
        {
            map[h][w] = ALIVE;
        }
    }
}

bool isAlive(int x, int y)
{
    return map[y][x] == ALIVE;
}