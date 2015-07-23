#include "Maze_lite.h"


//////////////////////////////////////////////////////////////////////////////////////////////
////					Tile_lite
//////////////////////////////////////////////////////////////////////////////////////////////



// setting the @param index
void Tile_lite::setIndex(int index) {
    Tile_lite::index = index;
}


// @returns the index
int Tile_lite::getIndex() {
    return index;
}


// setting the @param color of the tile_lite
void Tile_lite::setColor(sf::Color color) {
    TileColor = color;
}


// @returns the current color of the tile (default BLUE)
sf::Color Tile_lite::getColor() {
    return TileColor;
}


// setting in @param dir the wall to @param isWall
void Tile_lite::setWall(int dir, bool isWall) {
    if (isSurrounding(dir) ) wall[dir] = isWall;
}


// @returns if there's a wall in @param dir
bool Tile_lite::isWall(int dir) {
    return isSurrounding(dir) ? wall[dir] : true;
}


// setting the surrounding @param tile in @param dir
void Tile_lite::setSurrounding(int dir, Tile_lite* tile) {
    surrounding[dir] = tile;
}


// @returns the surrounding of the tile in @param dir
Tile_lite* Tile_lite::getSurrounding(int dir) {
    return isSurrounding(dir) ? surrounding[dir] : NULL;
}


// @returns if there's a tile surrounding this one in @param dir
bool Tile_lite::isSurrounding(int dir) {
    return surrounding[dir] != NULL;
}


// setting if there was food on this tile to @param isThere
// no amount since the value will change over time
void Tile_lite::setFood(bool isThere) {
    wasFoodOnIt = isThere;
}


// @returns if there was food on this tile once
bool Tile_lite::wasFood() {
    return wasFoodOnIt;
}


// setting if there once was scent on it to @param isThere
// no amount since the value will change over time
void Tile_lite::setScent(bool isThere) {
    wasScentOnIt = isThere;
}


// @returns if there once was scent on this tile
bool Tile_lite::wasScent() {
    return wasScentOnIt;
}


// @returns if there's a base on this tile
bool Tile_lite::isBase() {
    return current == BASE || current == BASE_ANT || current == BASE_RES || current == BASE_RES_ANT;
}


// @returns if there was an Ant on this tile TODO: relevant?
bool Tile_lite::hasAnt() {
    return current == ANT || current == RES_ANT || current == BASE_ANT || current == BASE_RES_ANT;
}


// @returns if there's a res on this tile
bool Tile_lite::isRes() {
    return current == RES || current == RES_ANT || current == BASE_RES || current == BASE_RES_ANT;
}



//////////////////////////////////////////////////////////////////////////////////////////
////					Maze_lite
//////////////////////////////////////////////////////////////////////////////////////////



// creating a maze with xSize time ySize fields
Maze_lite::Maze_lite(int xSize, int ySize) {
    sizeX = xSize;
    sizeY = ySize;
    MAP = std::vector<std::vector<Tile_lite>> ( (unsigned int) xSize,
            std::vector<Tile_lite>( (unsigned int) ySize ) );
    for (int i = 0; i < xSize; i++)
        for (int j = 0; j < ySize; j++)
            MAP[i][j].setIndex(i * ySize + j);
    setNeighbourTiles();
}

// setting the neighbouring tiles of the maze_lite
void Maze_lite::setNeighbourTiles() {
    for (int i = 0; i < sizeX; i++)
        for (int j = 0; j < sizeY; j++) {
            if (j > 0) MAP[i][j].setSurrounding(0, &MAP[i][j - 1]);
            if (i < sizeX - 1) MAP[i][j].setSurrounding(1, &MAP[i + 1][j]);
            if (j < sizeY - 1) MAP[i][j].setSurrounding(2, &MAP[i][j + 1]);
            if (i > 0) MAP[i][j].setSurrounding(3, &MAP[i - 1][j]);
        }
}


// @returns the xSize of the maze
int Maze_lite::getSizeX(){
    return sizeX;
}


// @returns the ySize of the maze
int Maze_lite::getSizeY(){
    return sizeY;
}


// @returns the max index of the maze
int Maze_lite::INDEX_MAX() {
    return sizeX * sizeY - 1;
}


// @returns the tile& at the @param index
Tile_lite& Maze_lite::getAtIndex(int index) {
    return MAP[index % sizeX][index / sizeX];
}



