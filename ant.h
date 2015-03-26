#ifndef ANT_H
#define ANT_H


#ifndef SOURCES
#define SOURCES "/home/bz/ClionProjects/AntWorld/resources/"
#endif


#include <SFML/Graphics/Texture.hpp>
#include "ticksystem.h"
#include "maze.h"

#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Ant : public tickInterface {

private:
    int locX = -1, locY = -1, dir = 0, height = 26, width = 26;

    unsigned int ownFood = 0;

    sf::Texture texture;
    sf::Sprite sprite;

    Tile *current;

    Maze *maze;

public:
    Ant();
    ~Ant();

    void setCurrent(Tile *current);

    void setPosition(Tile *tileToGoOn) { setCurrent(tileToGoOn); }

    void move(int dir);

    void draw(sf::RenderWindow *window);

    void senseFoodOnCurrentTile();

    void doTick();

    bool isInide(int x, int y);

};











#endif