#ifndef MAZE_H
#define MAZE_H


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>
#include "ticksystem.h"




class Tile : public tickInterface {
protected:
    int locX, locY, height, width, index = -1;

    unsigned int food = 0;

    // bool wall[4] = { false, false, false, false };
    bool wall[4] = { true, true, true, true };
//    the directions: up, right, down, left
//                     0 ,   1 ,   2 ,   3

    Tile *surrounding[4] = {}; // to direct to tiles next to it

    // RectangleShapes to draw the tile ad the walls later on
    sf::RectangleShape rect;
    sf::RectangleShape Walls[4];

    // adding or actualizing the Walls position
    void addWalls();

public:
    Tile(){};
    // setting the coordinates and the size of the tile
    void setSize(int x, int y, int width, int height);
    virtual int getX();         // returning x
    virtual int getY();         // returning y
    void move(int x, int y);    // moving it @param x and @param y pixels
    bool isInside(int x, int y);// returning if the mouse is inside the tile
    virtual int getHeight();    // getting the height of the Tile
    virtual int getWidth();     // getting the width of the Tile
    virtual void setIndex(int index); // setting the @param index
    virtual int getIndex() const; // the set index
    void setColor(sf::Color color); // setting the color of the Tile
    void draw(sf::RenderWindow *renderWindow); // drawing the Tile completely (obsolete)
    void drawTile(sf::RenderWindow *renderwindow); // drawing only the body of the Tile
    void drawWalls(sf::RenderWindow *renderWindow); // drawing only the Walls of the Tile
    void doTick();              // doing a Tick
    virtual void setWall(int dir, bool setWall); // setting the wall in @param dir to @param setWall
    bool isWall(int dir);       // returning if there is a wall in this @param dir
    void setSurrounding(int dir, Tile* tile); // setting in @param dir the @param tile
    virtual Tile* getSurrounding(int dir); // returning the tile in @param dir
    virtual bool isSurrounding(int dir); // returning if there even is sth in @param dir
    virtual int isFood(); // returning all the food on the Tile
    int getFood(); // returning 0 up to 10 max food and decreasing it on the Tile

};


class showTile : public Tile {
protected:
    int pubX = -1, pubY = -1, pubHeight, pubWidth, pubIndex = -1;
    unsigned int pubFood = 0;
    Tile *tileToShow = NULL;    // the tile that is being 'copied'

public:
    showTile(){};
    void operator=(Tile *tile); // for getting the right values
    int getHeight();    // returning the height
    int getWidth();     // returning the width
    int getX();         // returning x
    int getOwnX();
    int getY();         // returning y
    int getOwnY();
    void setIndex(int index); // setting the @param index
    int getIndex();     // returning the index
    int isFood();       // returning how much food there is on the Tile
    void setWall(int dir, bool setWall); // setting in @param dir the @param setWall
    void doTick();      // whatever happens at a tick TODO: updating the info
    bool isSurrounding(int dir); // returns if there virtually is a tile next to it in @param dir
    Tile* getSurrounding(int dir); // getting the virtually surrounding tile
    Tile* getTileToShow(); // returns the tile it 'copies' or at least shows

};







class Maze : public tickInterface {

protected:
    int sizeX = -1, sizeY = -1, tileHeight = 30, tileWidth = 30, x = 0, y = 0;
    std::vector<std::vector<Tile> > MAP;
    sf::RectangleShape OuterWalls[4];

    // drawing the outer walls of the Maze
    void drawOuterWalls(sf::RenderWindow *renderWindow);


public:
    Maze(int xSize, int ySize);    // setting up a maze with @param xSize x @param ySize tiles
    void setOuterWalls();           // setting or updating the OuterWalls
    void setNeighbourTiles();       // setting the surrounding Tiles
    void drawMaze(sf::RenderWindow *renderWindow); // drawing the maze a whole
    void move(int x, int y); // moving for @param x and @param y pixels - the whole maze
    void doTick();  // whatever happens at a tick is updated in the maze
    Tile *getTileClicked(int x, int y);    // returns the tile that got clicked on
    Tile *getTile(int index);      // getting the Tile at @param index
    Tile *getTile(int x, int y);   // getting the Tile at @param x and @param y
    int getSizeX();                 // returns the sizeX of the maze
    int getSizeY();                 // returns the sizeY of the maze
    int getX();                     // returns the xPos of the maze
    int getY();                     // returns the yPos of the maze
    int INDEX_MAX();                // returns the MAX Index of the maze
    ~Maze(){};
};


#endif
