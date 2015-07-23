//
// Created by bz on 03.04.15.
//

#include "tile.h"
#include "ant.h"



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


// adding the @param state to the current state
void Tile::addState(STATE state) {
    std::cout << "adding state " << state << " to tile " << index << std::endl;
    if ( (state == RES && !isRES() && res != NULL) || (state == BASE && !isBASE() && base != NULL)
            || (state == ANT && !hasAnt() && ownAnts.size() != 0 ) ) {
        int intNewState = (int) state + (int) current;
        std::cout << "previous state: " << (int) current;
        current = (STATE) intNewState;
        std::cout << " new state: " << (int) current << std::endl;
    }
}


// removing the @param state from the current (only ANT, RES or BASE)
bool Tile:: removeState(STATE state) {
    std::cout << "removing state " << state << " from tile " << index << std::endl;
    if ( (state == RES && isRES() && res == NULL) || (state == BASE && isBASE() && base == NULL )
            || (state == ANT && hasAnt() && ownAnts.size() == 0) ) {
        int intNewState = (int) current - (int) state;
        std::cout << "previous state: " << (int) current;
        current = (STATE) intNewState;
        std::cout << " new state: " << (int) current << std::endl;
        return true;
    }
    return false;
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
void Tile::draw(sf::RenderWindow *window) {
    drawTile(window);
    drawWalls(window);
}


// only drawing the Tile
void Tile::drawTile(sf::RenderWindow *window) {
    window->draw(rect);
}


// drawing the walls -> dependent on wall[x]
void Tile::drawWalls(sf::RenderWindow *window) {
    for (int x = 0; x < 4; x++) {
        if (wall[x])
            window->draw(Walls[x]);
    }
}


// updating things at a tick
void Tile::doTick() {
    // for implementation purposes
    if (isRES() )
        res->doTick();
    if (isBASE() )
        base->doTick();

    for (int i = 0; i < 3; i++)
        if (Scents[i] > 0)
            Scents[i]--;

    // if (getAnt()->getDead() )
        // removeAnt(getAnt()->getID() );
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
    if (isBASE() )
        return (int) base->isFood();
    else if (isRES() )
        return (int) res->getProduced();
    else return 0;
}


// @returns max 10 or how much food there's on res or the base, else 0
int Tile::getFood(Ant* ant) {
    if (isBASE() )
        return base->getFood(ant, 10 - ant->getFood() );
    else if (isRES() )
        return res->getFood();
    else return 0;
}



// returns the info about the tile, depending on the own state
std::string Tile::getTileInfo() {
    std::string additional = "";

    if (current == ANT || current == NORMAL)
        additional += "\nNormal Tile";

    if (isBASE() )
        additional += "\n- BaseTile\nTeamNum: " + std::to_string(base->getTeamNum() ) +
                        "\nIn Team: " + std::to_string(base->getAntCount() ) +
                        "/20";

    if (isRES() )
        additional += "\n- ResTile\nProduction:\n" + std::to_string( (int) res->getProductionRate() ) + "." +
                std::to_string( (int) (res->getProductionRate() * 10) % 10);

    if (hasAnt() )
        additional += "\n- with Ant";

    return "Info:\n"
        "\nIndex: " + std::to_string(getIndex() + 1) +
        "\nX: " + std::to_string(getX() ) +
        "\nY: " + std::to_string(getY() ) +
        "\n\nFood: " + std::to_string(isFood() ) +
        "\nHighest Scent: \n" + std::to_string(getScent(0) ) +
        "\nfrom: " + std::to_string(getScentID(0) ) +
        "\n" + additional;
}


// setting the base and adding the new state 'Base' to current
void Tile::setBase(antBase *base) {
    Tile::base = base;
    addState(BASE);
}


// removing a base that was set up until now
void Tile::removeBase() {
    Tile::base = NULL;
    removeState(BASE);
}


// setting the @param res on this tile
void Tile::setRes(producing*produ) {
    std::cout << "setting Tile " << index << " a RES" << std::endl;
    res = produ;
    addState(RES);
}


// removing the producing part
void Tile::removeRes() {
    res = NULL;
    removeState(RES);
}


// adding the @param ant to the 'current on tile' vector
void Tile::addAnt(Ant* ant) {
    ownAnts.push_back(ant);
    // addScent(ant);
    addState(ANT);
    setColor(sf::Color(0, 70, 255) );
}


// removing the Ant with the @param AntID from 'on the tile' if it is there
// @return: if the operation was successful
bool Tile::removeAnt(unsigned int AntID) {
    std::cout << "gotta remove " << AntID << " from tile " << getIndex() << std::endl;
    for (int i = 0; i < ownAnts.size(); i++)
        if (ownAnts[i]->getID() == AntID) {
            ownAnts.erase(ownAnts.begin() + i);
            removeState(ANT);
            return true;
        }
    return false;
}


// @returns the ant that got on this tile first
Ant* Tile::getAnt() {
    return ownAnts[0];
}


// @returns how many ants there are on this tile exactly
int Tile::getAntCount() {
    return (int) ownAnts.size();
}


// @return the scent that currently is on this tile at @param which
int Tile::getScent(int which) {
    if (which % 3 == which && which <= scentCount)
        return Scents[which];
    return -1;
}


// @returns the Scent from @param own ant if there's one, or -1
int Tile::getOwnScent(Ant* who) {
    for (int i = 0; i < 3; i++)
        if (scentID[i] == who->getID() )
            return Scents[i];
    return -1;
}


// @returns the strongest Team-scent
int Tile::getTeamScent(Ant* who) {
    int highest = -1;
    for (int i = 3; i < 3; i++)
        if (who->isInTeam( (unsigned int) scentID[i]) && highest < Scents[i])
            highest = Scents[i];
    return highest;
}


// @returns the scentID, meaning the ID of the ant that left that scent there
int Tile::getScentID(int which) {
    if (which % 3 == which && which < scentCount)
        return scentID[which];
    return -1;
}


// removes an existing scent or just adds it, saving the @param from AntID
void Tile::addScent(Ant* from) {

    if (scentCount > 0) {

        for (int i = scentCount - 1; i > 0; i--)
            Scents[i] = Scents[i - 1];
        for (int i = scentCount - 1; i > 0; i--)
            scentID[i] = scentID[i - 1];

        Scents[0] = 200;
        scentID[0] = from->getID();
        if (scentCount < 3) scentCount++;

    } else {
        Scents[0] = 200;
        scentID[0] = from->getID();
        scentCount++;
    }
}



// returns if there is a Base on this Tile
bool Tile::isBASE() {
    return (int) current >= 4;
}


// returns if this is a Resource - Tile
bool Tile::isRES() {
    return current == RES || current == RES_ANT || current == BASE_RES || current == BASE_RES_ANT;
}


// returns if there is at least one ant on this tile
bool Tile::hasAnt() {
    return (int) current % 2 == 1;
}




///////////////////////////////////////////////////////////////////
////                        producing
///////////////////////////////////////////////////////////////////



// @param loc: the tile it is on
void producing::setPosition(Tile* loc) {
    reloadImage();

    texture.setSmooth(true);

    sprite.setPosition(loc->getX() +2, loc->getY() +2);
    sprite.setScale(0.2, 0.2);

    tile = loc;
}


// setting the position to the showTile
void producing::setPosition(showTile* loc) {
    reloadImage();
    texture.setSmooth(true);

    sprite.setPosition(loc->getOwnX() +2, loc->getOwnY() +2);
    sprite.setScale(0.24, 0.24);

    tile = loc;
}


// reloading the at some point maybe corrupted image
void producing::reloadImage() {

    if (!texture.loadFromFile(SOURCES"leaf.png") )
        std::cout << "Error: couldn't load RES_Image";
    else
        sprite.setTexture(texture);
}


// setting the @param prod production rate of the tile
void producing::setProductionRate(float prod) {
    production = prod;
}


// setting if there's production to begin with
void producing::setProducing(bool nowprod) {
    isProducing = nowprod;
}


// @return if there's production on this tile at all to begin with
bool producing::getProducingState() {
    return isProducing;
}


// @return the production rate of this tile if there's production at all to begin with
float producing::getProductionRate() {
    return production;
}

// @return the current food on this tile with 'parts'
float producing::getProduced() {
    return produced;
}


// @return up to 10, or else rounded what there got produced on this tile already
int producing::getFood() {
    if (produced > 10) {
        produced -= 10;
        return 10;
    } else {
        int tmp = (int) produced;
        produced -= tmp;
        return tmp;
    }
}


// drawing the leaf-image on the @param window
void producing::draw(sf::RenderWindow* window) {
    if (isProducing)
        window->draw(sprite);
}


// adding the production rate to the food currently on this tile
void producing::doTick() {
    if (isProducing)
        produced += production;
}

// destructor of producing - necessary?
producing::~producing() {
    // ...
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
    if (tileToShow != NULL && dir % 4 == dir)
        return tileToShow->isSurrounding(dir);
    return false;
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



// returns the info about the selected tile
std::string showTile::getTileInfo() {
    if (tileToShow != NULL)
        return tileToShow->getTileInfo();
    return Tile::getTileInfo();
}


// removing the base from the selected Tile
void showTile::removeBase() {
    tileToShow->removeBase();
    removeState(BASE);
}


