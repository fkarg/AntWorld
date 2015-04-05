#ifndef ANT_H
#define ANT_H


#ifndef SOURCES
#define SOURCES "/usr/resources_coding/"
#endif


#include <SFML/Graphics/Texture.hpp>
#include "ticksystem.h"
#include "tile.h"

#include <iostream>
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Ant : public tickInterface {

protected:
    int locX = -1, locY = -1, dir = 0, height = 26, width = 26;

    unsigned int ownFood = 0, AntID;

    sf::Texture texture;
    sf::Sprite sprite;

    Tile *current;

public:
    Ant();

    int getX();             // returns the x-val of the ant
    int getY();             // returns the y-val of the ant
    int getDir();           // returns the current dir of the ant
    unsigned int getFood(); // returns the current food of the ant
    Tile* getCurrent();     // returns the tile the ant is currently on
    void setCurrent(Tile *current); // setting the tile the ant is currently on
    unsigned int getID();   // getting the AntID
    void setPosition(Tile *tileToGoOn) { setCurrent(tileToGoOn); } // see getCurrent
    virtual void move(int dir); // moving the ant if it is possible in @param dir
    virtual void draw(sf::RenderWindow *window); // draws the ant
    void senseFoodOnCurrentTile(); // TODO: sensing etc
    void doTick();          // doing a tick
    bool isInside(int x, int y); // returns if the ant got clicked

};






class showAnt : public Ant {

protected:
    int pubX = -1, pubY = -1;
    bool isVisible = false;
    showTile* showingTile;
    Ant* AntToShow;

public:
    showAnt();
    void operator=(Ant* newAnt); // overriding the operator= for a normal ant
    void setAnt(Ant* newAnt); // setting the ant explicitly
    void setDir(int dir); // setting the dir of the ant
    // setting the position of the showAnt on the showTile
    void setPosition(showTile *showTile1);
    void setVisible(bool visible); // setting the visibility (the focus) of the ant
    bool getVisible(); // returns if the ant is visible right now or not
    void move(int dir); // 'moving' the showAnt and the antToShow
    void draw(sf::RenderWindow *window); // drawing the ant if it is visible right now
    Ant* getAntShown(); // returns the ant currently shown, if visible
};






class antBase : public tickInterface {

private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<Ant> ownAnts;
    Tile *baseTile;
    int locX, locY, AntCount = 0;

public:
    antBase() { reloadBase(); }
    void reloadBase();
    void setPosition(int x, int y, float scale = 0.2);
    void setPosition(Tile *tile);
    void addAnt();
    void addAnt(Ant ant);
    void addAnts(int num);
    void drawAnts(sf::RenderWindow *window);
    void drawBase(sf::RenderWindow *window);
    void draw(sf::RenderWindow *window);
    void doTick();
    Ant *getAnt(unsigned int AntID);

};






#endif