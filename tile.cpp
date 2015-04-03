//
// Created by bz on 03.04.15.
//

#include "tile.h"



///////////////////////////////////////////////////////////////////
////                    Tile
///////////////////////////////////////////////////////////////////



// adding or updating the Walls of the Tile
void Tile::addWalls() {
    sf::RectangleShape temp;
    temp.setFillColor(sf::Color::Magenta);

    temp.setPosition(locX - 2, locY);
    temp.setSize(sf::Vector2f(width + 4, 2) );
    Walls[0] = temp;

    temp.setPosition(locX - 2, locY + height - 2);
    Walls[2] = temp;

    temp.setPosition(locX, locY - 2);
    temp.setSize(sf::Vector2f(2, height + 4) );
    Walls[3] = temp;

    temp.setPosition(locX + width - 2, locY - 2);
    Walls[1] = temp;
}


// creating the tile at @param x and @param y with @param width and @param height
void Tile::setSize(int x, int y, int width, int height) {
    locX = x;
    locY = y;
    Tile::height = height;
    Tile::width = width;

    addWalls();

    rect.setSize(sf::Vector2f(height, width) );
    setColor(sf::Color::Blue);
    rect.setPosition(sf::Vector2f(locX, locY) );
}


// returns the x location of the Tile
int Tile::getX() {
    return locX;
}


// returns the Y location of the Tile
int Tile::getY() {
    return locY;
}


// moves the Tile at @param x and @param y pixels
void Tile::move(int x, int y) {
    locX += x;
    locY += y;

    addWalls();

    rect.setPosition(locX, locY);
}


// returns if the @param x and @param y coordinates are inside the tile
bool Tile::isInside(int x, int y) {
    return locX <= x && locY <= y
           && locX + width >= x
           && locY + height >= y;
}


// returns the height of the Tile
int Tile::getHeight() {
    return height;
}


// returns the width of the Tile
int Tile::getWidth() {
    return width;
}


// setting the @param index
void Tile::setIndex(int index) {
    Tile::index = index;
}


// returns the index of the Tile
int Tile::getIndex() const {
    return index;
}


// setting the color of the Tile to the @param color
void Tile::setColor(sf::Color color) {
    rect.setFillColor(color);
}


// returns the current color lf the tile
sf::Color Tile::getTileColor() {
    return rect.getFillColor();
}


// drawing the Tile completely
void Tile::draw(sf::RenderWindow *renderWindow) {
    drawTile(renderWindow);
    drawWalls(renderWindow);
}


// only drawing the Tile
void Tile::drawTile(sf::RenderWindow *renderwindow) {
    renderwindow->draw(rect);
}


// drawing the walls -> dependent on wall[x]
void Tile::drawWalls(sf::RenderWindow *renderWindow) {
    for (int x = 0; x < 4; x++) {
        if (wall[x])
            renderWindow->draw(Walls[x]);
    }
}


// updating things at a tick
void Tile::doTick() {
    // for implementation purposes
}


// setting in @param dir the wall to @param setWall
void Tile::setWall(int dir, bool setWall) {
    if(isSurrounding(dir) )
        wall[dir] = setWall;
}


// returns if there is a Wall in @param dir
bool Tile::isWall(int dir) {
    if (isSurrounding(dir) )
        return wall[dir];
    return true;
}


// setting in @param dir the surrounding @param tile
void Tile::setSurrounding(int dir, Tile *tile) {
    surrounding[dir] = tile;
}


// getting the surrounding tile in @param dir
Tile* Tile::getSurrounding(int dir) {
    return surrounding[dir];
}


// returns if there is a tile surrounding in @param dir
bool Tile::isSurrounding(int dir) {
    return dir % 4 == dir && surrounding[dir] != NULL;
}


// returns if there is food on the tile and how much
int Tile::isFood() {
    return food;
}


// returns the current food on the tile but max. 10 at once
// decreases the food on the tile at the same time
int Tile::getFood() {
    if (food >= 10) {
        food -= 10;
        return 10;
    } else {
        int tmp = food;
        food = 0;
        return tmp;
    }
}






///////////////////////////////////////////////////////////////////
////                        showTile
///////////////////////////////////////////////////////////////////



// overrides the '=' operator for the @param tile
void showTile::operator=(Tile *tile) {
    tileToShow = tile;
    doTick();
}


// returns the height of the current tileToShow
int showTile::getHeight() {
    return height;
}


// returns the width of the current tileToShow
int showTile::getWidth() {
    return width;
}


// returns the X-pos of the tileToShow
int showTile::getX() {
    return pubX;
}


// returns the own X-pos
int showTile::getOwnX() {
    return locX;
}


// returns the Y-pos of the tileToShow
int showTile::getY() {
    return pubY;
}


// returns the own Y-pos
int showTile::getOwnY() {
    return locY;
}


// setting the @param index of the 'pub' tile
void showTile::setIndex(int index) {
    showTile::pubIndex = index;
}


// returns the index of the tileToShow
int showTile::getIndex() {
    return pubIndex;
}


// returns all the food of the tileToShow
int showTile::isFood() {
    return pubFood;
}


// setting in the @param dir the wall to @param setWall
void showTile::setWall(int dir, bool setWall) {
    if (dir % 4 == dir) {
        tileToShow->setWall(dir, setWall);
        wall[dir] = setWall;
    }
}


// actualizing whatever happened on the tile
void showTile::doTick() {
    if (tileToShow != NULL) {
        pubX = tileToShow->getX();
        pubY = tileToShow->getY();
        pubHeight = tileToShow->getHeight();
        pubWidth = tileToShow->getWidth();
        pubIndex = tileToShow->getIndex();
        pubFood = (unsigned) tileToShow->isFood();
        rect.setFillColor(tileToShow->getTileColor() );

        wall[0] = tileToShow->isWall(0);
        wall[1] = tileToShow->isWall(1);
        wall[2] = tileToShow->isWall(2);
        wall[3] = tileToShow->isWall(3);
    }
}


// returns if there is a tile virtually surrounding this tile in @param dir
bool showTile::isSurrounding(int dir) {
    return tileToShow->isSurrounding(dir);
}


// returns the tile in @param dir of the tileToShow
// (since there is no tile next to the showTile anyways)
Tile* showTile::getSurrounding(int dir) {
    return tileToShow->getSurrounding(dir);
}

// returns the tile that is being shown
Tile* showTile::getTileToShow() {
    return tileToShow;
}



