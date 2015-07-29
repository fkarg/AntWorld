#ifndef MAZE_H
#define MAZE_H


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

#include "ticksystem.h"
#include "tile.h"
#include "ant.h"
#include "maze_lite.h"





class Maze : public tickInterface {

private:
    int sizeX = -1, sizeY = -1, tileHeight = 30, tileWidth = 30, x = 0, y = 0;
    std::vector<std::vector<Tile> > MAP;
    antBase bases[5] = {};
    producing prods[5] = {};
    sf::RectangleShape OuterWalls[4];

    unsigned int basesNum = 0, prodsNum = 0;

    // drawing the outer walls of the Maze
    void drawOuterWalls(sf::RenderWindow *renderWindow);


public:
    Maze(int xSize, int ySize);     // setting up a maze with @param xSize x @param ySize tiles
    void setOuterWalls();           // setting or updating the OuterWalls
    void setNeighbourTiles();       // setting the surrounding Tiles
    void drawMaze(sf::RenderWindow *window); // drawing the maze a whole
    void move(int x, int y);        // moving for @param x and @param y pixels - the whole maze
    void doTick();                  // whatever happens at a tick is updated in the maze
    void setHome(int x, int y);     // setting the @param x and y tile to an homeTile
    void setHome(Tile* tile);       // setting the @param tile to an homeTile
    void setHome(antBase base, Tile *tile); // setting a specific @param base to @param tile
    void removeHome(Tile* tile);    // removing the 'Home' status from a tile
    void setRes(Tile* tile);        // setting the @param tile a ResourceTile
    void removeRes(Tile* tile);     // removing the Resource-part of the @param tile
    int getBasesNum() { return basesNum; } // returns how many bases have been registered
    antBase* getBase(int index);    // returns the base at the @param index
    Tile* getTileClicked(int x, int y); // returns the tile that got clicked on
    Tile* getTile(int index);       // getting the Tile at @param index
    Tile *getTile(int x, int y);    // getting the Tile at @param x and @param y
    int getSizeX();                 // returns the sizeX of the maze
    int getSizeY();                 // returns the sizeY of the maze
    int getX();                     // returns the xPos of the maze
    int getY();                     // returns the yPos of the maze
    int INDEX_MAX();                // returns the MAX Index of the maze

    void reloadgfx();               // reloads all possibly corrupted images

    ~Maze(){};                      // destructor of the Maze
};




#endif
