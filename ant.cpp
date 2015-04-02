#include "ant.h"


// creating the ant, loading the image and setting it
Ant::Ant() {
    if (!texture.loadFromFile(SOURCES"Ant.png") )
        std::cout << "Error loading Ant_Image" << std::endl;
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

    std::cout << "Ant: current Tile: " + std::to_string(current->getIndex() + 1) << std::endl;

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

    std::cout << "Ant: current Tile: " + std::to_string(current->getIndex() + 1) << std::endl;
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









// returns an showAnt, scale for 35p
showAnt::showAnt() {
    sprite.setScale(0.24, 0.24);
}


// setting the currently selected Ant
void showAnt::operator=(Ant *newAnt) {
    setAnt(newAnt);
}


// setting all the values for showing them (from the @param newAnt)
void showAnt::setAnt(Ant *newAnt) {
    AntToShow = newAnt;
    pubX = newAnt->getX();
    pubY = newAnt->getY();
    setDir(newAnt->getDir());
    ownFood = newAnt->getFood();
    current = newAnt->getCurrent();
    setVisible(true);
}


// setting the position of the showAnt relational to the @param showTile
void showAnt::setPosition(showTile *showTile1) {
    showingTile = showTile1;

    locX = showingTile->getOwnX() + 2;
    locY = showingTile->getOwnY() + 2;

    sprite.setPosition(sf::Vector2f(locX, locY) );
}


// setting the Dir of the showAnt to @param dir
void showAnt::setDir(int dir) {
    showAnt::dir = dir;
}


// setting the showAnt to @param visible or not
void showAnt::setVisible(bool visible) {
    setDir(AntToShow->getDir() );
    isVisible = visible;
    std::cout << "showAnt: visibility set to: " << visible << std::endl;
}


// returns if the showAnt is visible or not
bool showAnt::getVisible() {
    return isVisible;
}


// moving the selected Ant in @param dir or at least turning in this direction
void showAnt::move(int dir) {

    if (isVisible) {
        AntToShow->move(dir);

        switch (dir) {
            case 0:
                sprite.setPosition(sf::Vector2f(locX, locY));
                break;
            case 1:
                sprite.setPosition(sf::Vector2f(locX + showingTile->getWidth() - 4,
                                                locY));
                break;
            case 2:
                sprite.setPosition(sf::Vector2f(locX + showingTile->getWidth() - 4,
                                                locY + showingTile->getHeight() - 4));
                break;
            case 3:
                sprite.setPosition(sf::Vector2f(locX,
                                                locY + showingTile->getHeight() - 4));
                break;
            default:
                break;
        }
        sprite.setRotation(dir * 90);
    }
}


// drawing the showAnt on the @param window when visible
void showAnt::draw(sf::RenderWindow *window) {
    if (isVisible)
        window->draw(sprite);
}


// returns the selected Ant
Ant* showAnt::getAntShown() {
    if (isVisible)
        return AntToShow;
    return NULL;
}











// initializing texture and position, as well as Ants
AntBase::AntBase() {

    if (!texture.loadFromFile(SOURCES"Home_1.png") )
        std::cout << "Error loading Home_Image" << std::endl;
    else
        sprite.setTexture(texture);

    texture.setSmooth(true);

    // sprite.setScale(sf::Vector2f(30, 30) );

    // sprite.setColor(sf::Color(0, 255, 0, 255) );

    sprite.scale(sf::Vector2f(0.2, 0.2) );
}


// adding an @param ant
void AntBase::addAnt(Ant ant) {
    ownAnts.push_back(ant);
    antCount++;
}


// increasing the number of Ants in Conrol of this Base
void AntBase::addAnt() {
    Ant ant();
}


// drawing all Ants included to this Base
void AntBase::drawAnts(sf::RenderWindow *renderWindow) {
    for (int i = 0; i < ownAnts.size(); i++) {
        ownAnts[i].draw(renderWindow);
    }
}


// drawing the Tile itself
void AntBase::drawTile(sf::RenderWindow *window) {
    Tile::drawTile(window);
    window->draw(sprite);
}


void AntBase::doTick() {
    // TODO: doTick
}


// getting the Ant with the @param AntID or NULL instead
Ant* AntBase::getAnt(int AntID) {

    for (int i = 0; i < ownAnts.size(); i++) {
        if (ownAnts[i].getID() == AntID)
            return &ownAnts[i];
    }

    return NULL;
}











