
#ifndef ANTWORLD_TILE_H
#define ANTWORLD_TILE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "ticksystem.h"



class antBase;


class Tile : public tickInterface {
protected:
    int locX, locY, height, width, index = -1, special = 0;

    unsigned int food = 0;

    // bool wall[4] = { false, false, false, false };
    bool wall[4] = { true, true, true, true };
//    the directions: up, right, down, left
//                     0 ,   1 ,   2 ,   3

    Tile *surrounding[4] = {}; // to direct to tiles next to it

    // RectangleShapes to draw the tile and the walls later on
    sf::RectangleShape rect;
    sf::RectangleShape Walls[4];

    antBase *base = NULL;

    // adding or actualizing the Walls position
    void addWalls();

public:
    Tile(){};
    // setting the coordinates and the size of the tile
    virtual void setSize(int x, int y, int width, int height);
    virtual int getX();         // returning x
    virtual int getY();         // returning y
    void move(int x, int y);    // moving it @param x and @param y pixels
    bool isInside(int x, int y);// returning if the mouse is inside the tile
    virtual int getHeight();    // getting the height of the Tile
    virtual int getWidth();     // getting the width of the Tile
    virtual void setIndex(int index); // setting the @param index
    virtual int getIndex() const; // the set index
    void setColor(sf::Color color); // setting the color of the Tile
    sf::Color getTileColor();       // returns the current color of the tile
    void draw(sf::RenderWindow *window); // drawing the Tile completely (obsolete)
    virtual void drawTile(sf::RenderWindow *window); // drawing only the body of the Tile
    void drawWalls(sf::RenderWindow *window); // drawing only the Walls of the Tile
    void doTick();              // doing a Tick
    virtual void setWall(int dir, bool setWall); // setting the wall in @param dir to @param setWall
    bool isWall(int dir);       // returning if there is a wall in this @param dir
    void setSurrounding(int dir, Tile* tile); // setting in @param dir the @param tile
    virtual Tile* getSurrounding(int dir); // returning the tile in @param dir
    virtual bool isSurrounding(int dir); // returning if there even is sth in @param dir
    virtual int isFood(); // returning all the food on the Tile
    int getFood(); // returning 0 up to 10 max food and decreasing it on the Tile
    int getSpecial() { return special; } // returns if the tile is somewhat special
    void setSpecial(int special) { Tile::special = special; } // setting the 'special' value
    antBase *getBase() { return base; } // returns the antBase if one is set
    void setBase(antBase *base) { Tile::base = base; } // setting the antBase
};





class showTile : public Tile {

protected:
    int pubX = -1, pubY = -1, pubHeight, pubWidth, pubIndex = -1, special = 1;
    unsigned int pubFood = 0;
    Tile *tileToShow = NULL;    // the tile that is being 'copied'

public:
    showTile(){};
    void operator=(Tile *tile); // for getting the right values
    int getHeight();    // returning the height
    int getWidth();     // returning the width
    int getX();         // returning x
    int getOwnX();      // returning the own X value
    int getY();         // returning y
    int getOwnY();      // returning the own Y value
    void setIndex(int index); // setting the @param index
    int getIndex();     // returning the index
    int isFood();       // returning how much food there is on the Tile
    void setWall(int dir, bool setWall); // setting in @param dir the @param setWall
    void doTick();      // whatever happens at a tick TODO: updating the info
    bool isSurrounding(int dir); // returns if there virtually is a tile next to it in @param dir
    Tile* getSurrounding(int dir); // getting the virtually surrounding tile
    Tile* getTileToShow(); // returns the tile it 'copies' or at least shows

};











#endif

