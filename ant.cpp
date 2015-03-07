#include "ant.h"


// creating the ant, loading the image and setting it
Ant::Ant() {
    if (!texture.loadFromFile("resources/Ant.png") )
        std::cout << "Error loading AntImage" << std::endl;
    else
        sprite.setTexture(texture);

    texture.setSmooth(true);

    // sprite.setScale(sf::Vector2f(30, 30) );

    // sprite.setColor(sf::Color(0, 255, 0, 255) );

    sprite.scale(sf::Vector2f(0.2, 0.2) );
}


Ant::~Ant() {
    // dtr
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



// Reacting and moving to environmental changes
void Ant::doTick() {
    // TODO: what to do at a tick

    // TODO: sensing - reacting - moving
    // TODO: sensing: food/scent/wall/direction
    // TODO: reacting: ifFood/maxScent/noScent, deciding what to do
    // TODO: moving: doing what has been devided to do

    /*
     * Idea: multiThreading all sensing/reacting Ants after them
     * moving (multiThreaded) and wait for the next Tick
     */
}


