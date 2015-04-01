#include "ant.h"


// creating the ant, loading the image and setting it
Ant::Ant() {
    if (!texture.loadFromFile(SOURCES"Ant.png") )
        std::cout << "Error loading AntImage" << std::endl;
    else
        sprite.setTexture(texture);

    texture.setSmooth(true);

    // sprite.setScale(sf::Vector2f(30, 30) );

    // sprite.setColor(sf::Color(0, 255, 0, 255) );

    sprite.scale(sf::Vector2f(0.2, 0.2) );
}


// setting the @param current: tile the ant is currently on
// necessary for getting the location and setting the position
void Ant::setCurrent(Tile *current) {
    Ant::current = current;

    locX = current->getX() + 2;
    locY = current->getY() + 2;

    sprite.setPosition(sf::Vector2f(locX, locY) );
}


// letting the ant move in the direction @param dir
// avoiding going through walls, just turning in that direction then
void Ant::move(int dir) {
    Ant::dir = dir;

    if (current->isSurrounding(dir) && !current->isWall(dir) )
        setCurrent(current->getSurrounding(dir) );

    switch (dir) {
        case 0:
            sprite.setPosition(sf::Vector2f(locX, locY) );
            break;
        case 1:
            sprite.setPosition(sf::Vector2f(locX + current->getWidth() - 4,
                    locY) );
            break;
        case 2:
            sprite.setPosition(sf::Vector2f(locX + current->getWidth() - 4,
                    locY + current->getHeight() - 4) );
            break;
        case 3:
            sprite.setPosition(sf::Vector2f(locX,
                    locY + current->getHeight() - 4) );
            break;
        default:break;
    }

}


// turning the ant and drawing it at the @param window
void Ant::draw(sf::RenderWindow *window) {

    sprite.setRotation(90 * dir);

    window->draw(sprite);
}


void Ant::senseFoodOnCurrentTile() {
    if (current->isFood() > 0)
        ownFood += current->getFood();
}


// Reacting and moving to environmental changes
void Ant::doTick() {
    // TODO: what to do at a tick

    // TODO: sensing - reacting - moving
    // - sensing: food/scent/wall/direction
    // - reacting: ifFood/maxScent/noScent, deciding what to do
    // - moving: doing what has been decided to do

    /*
     * Idea: multiThreading all sensing/reacting Ants after them
     * moving (multiThreaded) and wait for the next Tick
     */
}


// returns if the @param x and @param y are inside the Ant
bool Ant::isInside(int x, int y) {

    return x <= locX + height && x >= locX &&
            y <= locY + width && y >= locY;

}


// returns the X coordinate of the Ant
int Ant::getX() {
    return locX;
}


// returns the Y coordinate of the Ant
int Ant::getY() {
    return locY;
}


// returns the current direction of the Ant
int Ant::getDir() {
    return dir;
}


// returns how much food the Ant is carrying
unsigned int Ant::getFood() {
    return ownFood;
}


// returns the ID of the Ant
unsigned int Ant::getID() {
    return AntID;
}


// returns the Tile the Ant is currently on
Tile* Ant::getCurrent() {
    return current;
}









void showAnt::operator=(Ant *newAnt) {
    setAnt(newAnt);
}


void showAnt::setAnt(Ant *newAnt) {
    locX = newAnt->getX();
    locY = newAnt->getY();
    setDir(newAnt->getDir());
    ownFood = newAnt->getFood();
    current = newAnt->getCurrent();
}


void showAnt::setDir(int dir) {
    showAnt::dir = dir;
}


void showAnt::setVisible(bool visible) {
    show = visible;
}



void showAnt::move(int dir) {
    setVisible(false);
}













void AntBase::addAnt(Ant ant) {
    ownAnts.push_back(ant);
    antCount++;
}



void AntBase::drawAll(sf::RenderWindow *renderWindow) {
    for (int i = 0; i < ownAnts.size(); i++) {
        ownAnts[i].draw(renderWindow);
    }
}



void AntBase::doTick() {
    // TODO: doTick
}



Ant* AntBase::getAnt(int AntID) {
    // getting the Ant with the ID
    return NULL;
}











