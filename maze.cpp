#include "maze.h"


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
    return pubHeight;
}


// returns the width of the current tileToShow
int showTile::getWidth() {
    return pubWidth;
}


// returns the X-pos of the tileToShow
int showTile::getX() {
    return pubX;
}


// returns the Y-pos of the tileToShow
int showTile::getY() {
    return pubY;
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





///////////////////////////////////////////////////////////////////
////                        Maze
///////////////////////////////////////////////////////////////////



// (private) drawing the outer walls of the maze
void Maze::drawOuterWalls(sf::RenderWindow *renderWindow) {
    for (int x = 0; x < 4; x++) {
        renderWindow->draw((OuterWalls[x] ) );
    }
}


// initiating a maze with @param xSize times @param ySize Tiles
Maze::Maze(int xSize, int ySize) {
    sizeX = xSize;
    sizeY = ySize;
    MAP = std::vector<std::vector<Tile> >( (unsigned int) xSize,
            std::vector<Tile>( (unsigned int) ySize) );
    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            Tile tile;
            tile.setSize(i * (tileWidth), j * (tileHeight), tileWidth, tileHeight);
            tile.setIndex(i * xSize + j);
            MAP[i][j] = tile;
        }
    }
    setNeighbourTiles();
    setOuterWalls();
}


// setting or actualizing the outerWalls of the Maze
void Maze::setOuterWalls() {

    sf::RectangleShape temp;
    temp.setFillColor(sf::Color::Magenta);

    temp.setPosition(x - 3, y - 3);

    temp.setSize(sf::Vector2f(sizeX * tileWidth + 6, 3));

    OuterWalls[0] = temp;

    temp.setSize(sf::Vector2f(3, sizeY * tileHeight + 6));

    OuterWalls[3] = temp;

    temp.setPosition(sf::Vector2f(x + 3 + sizeX * tileWidth,
            y + 3 + sizeY * tileWidth));

    temp.setSize(sf::Vector2f(-(sizeX * tileWidth + 6), -3));

    OuterWalls[2] = temp;

    temp.setSize(sf::Vector2f(-3, -(sizeY * tileHeight + 6)));

    OuterWalls[1] = temp;
}


// setting the neighbourTile of each tile in the maze
void Maze::setNeighbourTiles() {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            if (j > 0)
                MAP[i][j].setSurrounding(0, &MAP[i][j - 1]);
            if (i < sizeX - 1)
                MAP[i][j].setSurrounding(1, &MAP[i + 1][j]);
            if (j < sizeY - 1)
                MAP[i][j].setSurrounding(2, &MAP[i][j + 1]);
            if (i > 0)
                MAP[i][j].setSurrounding(3, &MAP[i - 1][j]);
        }
    }
}


// drawing the whole maze (first tiles, then walls, then OuterWalls)
void Maze::drawMaze(sf::RenderWindow *renderWindow) {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            MAP[i][j].drawTile(renderWindow);
        }
    }
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            MAP[i][j].drawWalls(renderWindow);
        }
    }
    drawOuterWalls(renderWindow);
}


//moving the whole maze for @param x and @param y pixels
void Maze::move(int x, int y) {
    Maze::x += x;
    Maze::y += y;
    setOuterWalls();
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            MAP[i][j].move(x, y);
        }
    }
}


// doing the tick for every tile
void Maze::doTick() {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            MAP[i][j].doTick();
        }
    }
}


// returns the tile that got clicked on (if there is one)
Tile* Maze::getTileClicked(int x, int y) {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            if (MAP[i][j].isInside(x, y) )
                return &MAP[i][j];
        }
    }
    return NULL;
}


// returns the tile at the @param index
Tile* Maze::getTile(int index) {
    return &MAP[index / sizeX][index % sizeY];
}


// returning the tile at the @param x and @param y coordinates
Tile* Maze::getTile(int x, int y) {
    return &MAP[x][y];
}


// returning the sizeX of the maze
int Maze::getSizeX() {
    return sizeX;
}


// returning the the sizeY of the the maze
int Maze::getSizeY() {
    return sizeY;
}


// returns the xPos of the maze
int Maze::getX() {
    return x;
}


// returns the yPos of the maze
int Maze::getY() {
    return y;
}


// returning the max index of the maze
int Maze::INDEX_MAX() {
    return sizeX * sizeY;
}


