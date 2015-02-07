#include <SFML/Graphics/Color.hpp>
#include "Tile.h"
#include "../include/Tile.h"

Tile::Tile(int x, int y, int height, int width)
{
    locX = x;
    locY = y;
    ::height = height;
    ::width = width;

    tile.setSize(Vector2f(height, width));
    tile.setFillColor(Color::Blue);

    //ctor
}

Tile::~Tile()
{
    //dtor
}

bool Tile::isWall(int dir){
    return walls[dir];
}


void Tile::drawTile(RenderWindow *renderWind){
    renderWind->draw(tile);
}
