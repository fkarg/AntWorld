#ifndef MAZECREATOR_H
#define MAZECREATOR_H

#include "maze.h"
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include "ticksystem.h"



// creates a @param maze Random maze
class RandomCreator : public tickInterface {
private:
    int runs = -1, tick = -1;   // how many ticks it should go on,
                                // and how many have already happened

    Maze *mazetoDo;             // the maze to be modified

public:
    RandomCreator(){};
    void setMaze(Maze *maze);
    void doTicks(int num = 1);
    void reset();
    void doTick();
    void complete();
};



// testing if there is a connection between two tiles
// with the A* search algorithm
class Craver : public tickInterface {
private:
    bool startSet = false, aimSet = false, mazeSet = false;
    Tile *startTile = NULL, *aimTile = NULL;
    Maze *maze = NULL;

    sf::Color colorTiles = sf::Color(sf::Color::Blue);

    void ColorTiles(std::vector<Tile*> tiles);

    void out(std::string msg) {
        std::cout << "Craver: " + msg << std::endl;
    }

public:
    void setStart(Tile *startTile); // setting the startTile of the search
    void setAim(Tile *aimTile); // setting the aim of the search
    void setMaze(Maze *maze); // setting the maze in which there is searched

    void colorPath(sf::Color color); // coloring the found path

    void doTick(); // what happens at a tick ? nothing actually

    bool searchAStar(); // starting the A* search, returns if it was successful

    // returns the index of the path closest to the aimTile
    int IndexOfClosestToTile(std::vector<std::vector<Tile *> > allPaths);

    // returns if the @param currentTile got already included in the current path
    bool alreadyIncluded(std::vector<Tile*> path, Tile *currentTile);

    // returns the absolute distance from the @param currentTile to the aimTile
    int getDistToAim(Tile* currentTile);
};


// creating a 'perfect' fractured maze, not-so-perfect when
// some walls or free spaces are there already
class perfectCreator : public tickInterface {
private:

    // the vector that keeps track of the connections
    std::vector<std::vector<int> > visitable;

    Maze *maze; // the maze that will get a 'perfect' solution

    bool mazeSet = false; // the bool that keeps track if the maze has been set

    // initiating the vector after it is known, what size is needed
    void initVec();

    // replacing every @param oldNum with @param newNum
    void replaceEvery(int oldNum, int newNum);

    void out(std::string msg) {
        std::cout << "perfCreator: " + msg << std::endl;
    }

    // returns if all tiles era connected already
    bool areAllConnected();

    // returns if two tiles next to each other
    // (tile at @param x and y in direction @param dir)
    bool areDirectlyConnected(int x, int y, int dir);

public:

    void setMaze(Maze *maze); // setting the @param maze

    bool start(); // returning if the creation was successful or not

    // connecting the tile at @param x and y in @param dir if not connected already
    void connect(int X, int Y, int dir);

    void mazeChanged(); // reinitialises the connections in the maze

    void doTick(); // a Tick ... but ... nothing happens

    void ResetMaze(); // resetting the maze to the original state

};








#endif