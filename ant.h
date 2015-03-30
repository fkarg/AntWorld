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

protected:
    int locX = -1, locY = -1, dir = 0, height = 26, width = 26;

    unsigned int ownFood = 0, AntID;

    sf::Texture texture;
    sf::Sprite sprite;

    Tile *current;

    Maze *maze;

    int getX();
    int getY();
    int getDir();
    unsigned int getFood();
    Tile* getCurrent();


public:
    Ant();

    void setCurrent(Tile *current);

    unsigned int getID();

    void setPosition(Tile *tileToGoOn) { setCurrent(tileToGoOn); }

    virtual void move(int dir);

    void draw(sf::RenderWindow *window);

    void senseFoodOnCurrentTile();

    void doTick();

    bool isInside(int x, int y);

    friend void showAnt::setAnt(Ant *newAnt);

};






class showAnt : public Ant {

protected:
    int pubX = -1, pubY = -1;
    bool show = false;

public:
    void operator=(Ant* newAnt);
    void setAnt(Ant* newAnt);
    void setDir(int dir);
    void setVisible(bool visible);
    void move(int dir);
};






class AntBase : tickInterface {

protected:
    std::vector<Ant> ownAnts;
    int antCount = 0;


public:
    void drawAll(sf::RenderWindow *renderWindow);
    void addAnt(Ant ant);
    void doTick();
    Ant* getAnt(int AntID);
};





#endif