#include "Tile.h"

Tile::Tile(int x, int y, int height, int width)
{
    locX = x;
    locY = y;
    ::height = height;
    ::width = width;



    //ctor
}

Tile::~Tile()
{
    //dtor
}

bool Tile::isWall(int dir){
    return walls[dir];
}


void Tile::drawTile(const RenderWindow& renderWind){
    renderWind.draw(tile);
}
