#include "maze.h"


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


int Tile::getX() {
    return locX;
}


int Tile::getY() {
    return locY;
}


void Tile::move(int x, int y) {
    locX += x;
    locY += y;

    addWalls();

    rect.setPosition(locX, locY);
}


bool Tile::isInside(int x, int y) {
    return locX <= x && locY <= y
            && locX + width >= x
            && locY + height >= y;
}


int Tile::getHeight() {
    return height;
}


int Tile::getWidth() {
    return width;
}


void Tile::setIndex(int index) {
    Tile::index = index;
}


int Tile::getIndex() const {
    return index;
}


void Tile::setColor(sf::Color color) {
    rect.setFillColor(color);
}


void Tile::draw(sf::RenderWindow *renderWindow) {
    drawTile(renderWindow);
    drawWalls(renderWindow);
}


void Tile::drawTile(sf::RenderWindow *renderwindow) {
    renderwindow->draw(rect);
}


void Tile::drawWalls(sf::RenderWindow *renderWindow) {
    for (int x = 0; x < 4; x++) {
        if (wall[x])
            renderWindow->draw(Walls[x]);
    }
}


void Tile::doTick() {
    // for implementation purposes
}


void Tile::setWall(int dir, bool setWall) {
    if(isSurrounding(dir) )
        wall[dir] = setWall;
}

bool Tile::isWall(int dir) {
    if (isSurrounding(dir) )
        return wall[dir];
    return true;
}


void Tile::setSurrounding(int dir, Tile *tile) {
    surrounding[dir] = tile;
}


Tile* Tile::getSurrounding(int dir) {
    return surrounding[dir];
}


bool Tile::isSurrounding(int dir) {
    return dir % 4 == dir && surrounding[dir] != NULL;
}



int Tile::isFood() {
    return food;
}


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








void showTile::operator=(Tile *tile) {
    tileToShow = tile;
    doTick();
}


int showTile::getHeight() {
    return pubHeight;
}


int showTile::getWidth() {
    return pubWidth;
}


int showTile::getX() {
    return pubX;
}


int showTile::getY() {
    return pubY;
}


void showTile::setIndex(int index) {
    showTile::pubIndex = index;
}


int showTile::getIndex() {
    return pubIndex;
}


int showTile::isFood() {
    return pubFood;
}


void showTile::setWall(int dir, bool setWall) {
    if (dir % 4 == dir) {
        tileToShow->setWall(dir, setWall);
        wall[dir] = setWall;
    }
}


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


bool showTile::isSurrounding(int dir) {
    return tileToShow->isSurrounding(dir);
}


Tile* showTile::getSurrounding(int dir) {
    return tileToShow->getSurrounding(dir);
}


Tile* showTile::getTileToShow() {
    return tileToShow;
}






void Maze::drawOuterWalls(sf::RenderWindow *renderWindow) {
    for (int x = 0; x < 4; x++) {
        renderWindow->draw((OuterWalls[x] ) );
    }
}


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


void Maze::doTick() {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            MAP[i][j].doTick();
        }
    }
}


Tile* Maze::getTileClicked(int x, int y) {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            if (MAP[i][j].isInside(x, y) )
                return &MAP[i][j];
        }
    }
    return NULL;
}


Tile* Maze::getTile(int index) {
    return &MAP[index / sizeX][index % sizeY];
}


Tile* Maze::getTile(int x, int y) {
    return &MAP[x][y];
}


int Maze::getSizeX() {
    return sizeX;
}


int Maze::getSizeY() {
    return sizeY;
}


int Maze::INDEX_MAX() {
    return sizeX * sizeY;
}