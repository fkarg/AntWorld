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

    int getX();
    int getY();
    int getDir();
    unsigned int getFood();
    Tile* getCurrent();


    void setCurrent(Tile *current);

    unsigned int getID();

    void setPosition(Tile *tileToGoOn) { setCurrent(tileToGoOn); }

    virtual void move(int dir);

    virtual void draw(sf::RenderWindow *window);

    void senseFoodOnCurrentTile();

    void doTick();

    bool isInside(int x, int y);

};






class showAnt : public Ant {

protected:
    int pubX = -1, pubY = -1;
    bool isVisible = false;
    showTile* showingTile;
    Ant* AntToShow;

public:
    showAnt();
    void operator=(Ant* newAnt);
    void setAnt(Ant* newAnt);
    void setPosition(showTile *showTile1);
    void setDir(int dir);
    void setVisible(bool visible);
    bool getVisible();
    void move(int dir);
    void draw(sf::RenderWindow *window);
    Ant* getAntShown();
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