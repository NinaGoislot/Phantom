#pragma once



//-----------------------------------------------------------------------------------------
//---------------------------------------- INCLUDE ----------------------------------------
//-----------------------------------------------------------------------------------------

#include <iostream>
#include <ctime>
#include <random>

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

//-----------------------------------------------------------------------------------------
//-------------------------------------- FUNCTIONS ----------------------------------------
//-----------------------------------------------------------------------------------------

// generation de la map
void initializeMap();
void generateMap(int generations);

// fonction qui compte le nombre de voisins vivants
int countAliveNeighbors(int x, int y);

// definition de la taille du spawn
void playerSpawner(int size);

// vérifie si la case est vivante
bool isAlive(int x, int y);

// détruit la case (action de creuser)
void digTile(int x, int y);

// fonction d'affichage de la map
void displayMap();