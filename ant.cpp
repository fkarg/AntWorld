#include "ant.h"


// creating the ant, loading the image and setting it
Ant::Ant() {

    // FIXME: there will be a white tile (probably) when drawn
    // this comes from: the texture is getting copied
    // and (probably) loses the image in the process

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







// reloading the base-Image (needed when transferring 'ownership')
void antBase::reloadBase() {
    if (!texture.loadFromFile(SOURCES"Home_2.png") )
        std::cout << "Error Loading Home_Image" << std::endl;
    else
        sprite.setTexture(texture);

    texture.setSmooth(true);
}


// setting the Position and the scale of the sprite and the texture
void antBase::setPosition(int x, int y, float scale) {
    locX = x + 2;
    locY = y + 2;
    sprite.setPosition(locX, locY);
    sprite.scale(scale, scale);
}


// setting the position of the sprite to the position of the @param tile
void antBase::setPosition(Tile *tile) {
    baseTile = tile;
    setPosition(tile->getX(), tile->getY(), 0.2);
}


// adding a new ant
void antBase::addAnt() {
    Ant ant;
    ant.setPosition(baseTile);
    ownAnts.push_back(ant);
    AntCount++;
}


// adding a specific @param ant to the ownAnts
void antBase::addAnt(Ant ant) {
    ownAnts.push_back(ant);
    AntCount++;
}


// adding @param num new general ants
void antBase::addAnts(int num) {
    for (int i = 0; i < num; i++)
        addAnt();
}


// drawing the ants from the antBase
void antBase::drawAnts(sf::RenderWindow *window) {
    for (int i = 0; i < AntCount; i++)
        ownAnts[i].draw(window);
}


// drawing the sprite of the antBase
void antBase::drawBase(sf::RenderWindow *window) {
    window->draw(sprite);
}


// drawingn the antBase and the Ants of the antBase
void antBase::draw(sf::RenderWindow *window) {
    drawBase(window);
    drawAnts(window);
}


// doing the tick for all ants too
void antBase::doTick() {
    for (int i = 0; i < AntCount; i++)
        ownAnts[i].doTick();
}


// returns the ant with the @param AntID or NULL if notexistent
Ant* antBase::getAnt(unsigned int AntID) {
    for (int i = 0; i < AntCount; i++) {
        if (ownAnts[i].getID() == AntID)
            return &ownAnts[i];
    }
    return NULL;
}






