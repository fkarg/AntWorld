#include "../include/Maze.h"

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


void Maze::drawMaze(RenderWindow *renderWind){
    for(int i = 0; i < sizeX; i++){
        for(int j = 0; j < sizeY; j++){
        }
    }
    Tile tile1(10, 10, 20, 20);

    tile1.drawTile(renderWind);

}
