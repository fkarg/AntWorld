#include "Maze.h"

Maze::Maze(int sizeX, int sizeY)
{
    ::sizeX = sizeX;
    ::sizeY = sizeY;
    //ctor
}

Maze::~Maze()
{
    //dtor
}


Maze::drawMaze(const RenderWindow& renderWind){
    for(int i = 0; i < sizeX; i++){
        for(int j = 0; j < sizeY; j++){
            // TODO: draw Tile in Map!
        }
    }
}
