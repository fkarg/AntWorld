#include "ant.h"
#include "maze.h"



// creating the ant, loading the image and setting it
Ant::Ant() {

    reloadImage();

    setAntID(MAXANTID);
    MAXANTID++;

    sprite.scale(sf::Vector2f(0.2, 0.2) );

}


// reloads the maybe corrupted Image of the Ant
void Ant::reloadImage() {

    if (!texture.loadFromFile(SOURCES"Ant.png") )
        std::cout << "Error loading Ant_Image" << std::endl;
    else
        sprite.setTexture(texture);

    texture.setSmooth(true);

    // sprite.setScale(sf::Vector2f(30, 30) );

    // sprite.setColor(sf::Color(0, 255, 0, 255) );

    sprite.setColor(sf::Color(255, 255, 255, 200) );

    if (current != NULL) {
        current->removeAnt(AntID);
        if (!isDead) current->addAnt(this);
    }
}


// setting the Home of the Ant and the TeamNum
void Ant::setHome(antBase* home) {
    Ant::home = home;
    TeamNum = home->getTeamNum();
}


// setting the @param current: tile the ant is currently on
// necessary for getting the location and setting the position
void Ant::setCurrent(Tile *current) {
    if (Ant::current != NULL)
        Ant::current->removeAnt(AntID);

    Ant::current = current;

    locX = current->getX() + 2;
    locY = current->getY() + 2;

    sprite.setPosition(sf::Vector2f(locX, locY) );

    if (!isDead) current->addAnt(this);
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

    std::cout << "Ant: " << AntID << " current Tile: " + std::to_string(current->getIndex() + 1) << std::endl;
}


// turning the ant and drawing it at the @param window
void Ant::draw(sf::RenderWindow *window) {

    sprite.setRotation(90 * dir);

    if (!isDead)
        window->draw(sprite);
}


void Ant::senseFoodOnCurrentTile() {
    if (current->isFood() > 0)
        addFood( (unsigned int) current->getFood() );
}


// Reacting and moving to environmental changes
void Ant::doTick() {

    testLiving();

    if (!isDead) {
        senseFoodOnCurrentTile();
        if (current->isBASE())
            BaseFoodCommunicate();
        current->addScent(this);
    }

    // TODO: test if food carrying

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


// Ant 'dies', meaning it somehow didn't get enough food or got removed from the base
void Ant::Dies() {
    std::cout << "removing from the tile " << current->getIndex() << std::endl;
    current->removeAnt(AntID);
    isDead = true;
    if (home != NULL)
        home->decRealAntCount(this);
}


// Ant has been dead but is needed somewhere else, so it is reused
void Ant::relive(Tile* pos) {
    dir = 0;
    setPosition(pos);
    isDead = false;
    livingForTicks = 5;
}


// @returns if @param AntID is in the own team
bool Ant::isInTeam(unsigned int AntID) {
    for (int i = 0; i < home->getAntCount(); i++) {
        Ant* tmp = home->getAnt(i);
        if (tmp != NULL) if (tmp->getID() == AntID)
            return true;
    }
    return false;
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


void Ant::addFood(unsigned int number) {
    if (number + ownFood > MAX_FOOD_ANT_CARRYING)
        ownFood = MAX_FOOD_ANT_CARRYING;
    else if (number + ownFood < MAX_FOOD_ANT_CARRYING)
        ownFood += number;
}


void Ant::BaseFoodCommunicate() {
    if (ownFood < 10)
        addFood(current->getBase()->getFood(this, 10 - ownFood) );
    else if (ownFood > 10)
        current->getBase()->addFood(ownFood - 10), ownFood -= (ownFood - 10);

}


// setting the @param unique AntID
void Ant::setAntID(unsigned int newID) {
    AntID = newID;
}


// returns the ID of the Ant
unsigned int Ant::getID() {
    return AntID;
}


// returns the Tile the Ant is currently on
Tile* Ant::getCurrent() {
    return current;
}


// returns the number of ticks the ant will be alive for at least
unsigned int Ant::getTicksLiving() {
    return livingForTicks;
}


// testing if the ant is still alive or only a ghost
void Ant::testLiving() {
    if (!isDead) {
        livingForTicks--;
        if (livingForTicks <= 2) if (ownFood > 0)
            ownFood--, livingForTicks += 10;
        if (livingForTicks <= 0) Dies();
    }
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
void showAnt::setAnt(Ant* newAnt) {
    AntToShow = newAnt;
    pubX = newAnt->getX();
    pubY = newAnt->getY();
    setDir(newAnt->getDir());
    ownFood = newAnt->getFood();
    current = newAnt->getCurrent();
    setVisible(!newAnt->getDead() );
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
    setPosition(dir);
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

        setDir(dir);
    }
}


// setting the Position relational to the @param dir
void showAnt::setPosition(int dir) {
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


// whatever happens at a tick gets actualized
void showAnt::doTick() {
    std::cout << "setting visible or not" << std::endl;
    if (AntToShow != NULL)
        if (AntToShow->getDead() )
            setVisible(false);
}










// reloading the base-Image (needed when transferring 'ownership')
void antBase::reloadBase() {
    if (!texture.loadFromFile(SOURCES"Home_1.png") )
        std::cout << "Error Loading Home_Image" << std::endl;
    else
        sprite.setTexture(texture);

    texture.setSmooth(true);

    // for (int i = 0; i < AntCount; i++)
        // ownAnts[i].reloadImage();
}


// setting the @param maze
void antBase::setMaze(Maze *maze) {
    antBase::maze = maze;
}


// setting the Position and the scale of the sprite and the texture
void antBase::setPosition(int x, int y, float scale) {
    locX = x + 2;
    locY = y + 2;
    sprite.setPosition(locX, locY);
    sprite.scale(scale, scale);
}


// setting the position of the sprite to the position of the @param tile
void antBase::setPosition(Tile *tile, float scale) {
    setBase(tile);
    setPosition(tile->getX(), tile->getY(), scale);
}


// adding a new ant
void antBase::addAnt() {
    // FIXME: currently crashing under broad conditions, and not always either
    // meaning I haven't figuered out what causes it
    Ant ant;
    if (AntCount == 20)
        ant = ownAnts[getDeadIt()],
        deadCount--,
        ant.relive(baseTile),
        addAnt(ant);
    else {
        ant = ownAnts[AntCount];
        ant.setPosition(baseTile);
        ant.setHome(this);
        addAnt(ant);
    }
}


// adding a specific @param ant to the ownAnts
void antBase::addAnt(Ant ant) {
    if (AntCount == 20) {
        ownAnts[getDeadIt()] = ant;
        dead[getDeadIt()] = false;
        deadCount--;
        RealAntCount++;
    } else {
        ownAnts[AntCount] = ant;
        AntCount++;
        RealAntCount++;
    }
    for (int i = 0; i < AntCount; i++)
        ownAnts[i].reloadImage();
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
    if (isVisible)
        window->draw(sprite);
}


// drawing the antBase and the Ants of the antBase
void antBase::draw(sf::RenderWindow *window) {
    drawBase(window);
    drawAnts(window);
}


// doing the tick for all ants too
void antBase::doTick() {
    if (baseTile != NULL)
        if (baseTile->isFood() > 0 )
            food += baseTile->getFood();
    for (int i = 0; i < AntCount; i++)
        ownAnts[i].doTick();
}


// returns the ant with the @param AntID or NULL if nonexistent
Ant* antBase::getAnt(unsigned int AntID) {
    for (int i = 0; i < AntCount; i++) {
        if (ownAnts[i].getID() == AntID)
            return &ownAnts[i];
    }
    return NULL;
}


// @returns the ant at @param index, valid for everything smaller than the realAntCount
Ant* antBase::getAnt(int Index) {
    if (Index % 20 == Index && RealAntCount > 0) {
        int RealIndex = 0;
        for (int i = 0; i < Index; i++, RealIndex++)
            for (int j = 0; j < 20 && dead[RealIndex]; j++)
                RealIndex++;
        if (RealIndex % 20 == RealIndex)
            return &ownAnts[RealIndex];
    }
    return NULL;
}


// adding food to the base, not the tile directly since It'd get lost otherwise
void antBase::addFood(unsigned int number) {
    food += number;
}


// @returning food for the @param ant, testing if it is one of the own first
unsigned int antBase::getFood(Ant* ant, unsigned int number) {
    if (number > 24)
        number = 24;
    if (ant->getTeamNum() == TeamNum) {
        food -= number;
        return number; // number is ten by default
    } else return 0;
}


// @return the number of food there is on this base
unsigned int antBase::isFood() {
    return food;
}


// decreasing the Real AntCount and adding the ant to 'reactivatable' ones
void antBase::decRealAntCount(Ant* ant) {

    for (int i = 0; i < 20; i++)
        if (ant == &ownAnts[i]) {
            dead[i] = true;
            RealAntCount--;
            deadCount++;
            break;
        }

    // dead[deadCount] = true;

}


// getting the iterator of an dead ant
int antBase::getDeadIt() {
    for (int i = 0; i < 20; i++)
        if (dead[i])
            return i;
    return 0;
}

