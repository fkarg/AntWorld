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
    RandomCreator(Maze *maze);
    void changeMaze(Maze *maze);
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
    void setStart(Tile *startTile);
    void setAim(Tile *aimTile);
    void setMaze(Maze *maze);

    void colorPath(sf::Color color);

    void doTick();

    bool searchAStar();

    int IndexOfClosestToTile(std::vector<std::vector<Tile *> > allPaths);

    bool alreadyIncluded(std::vector<Tile*> path, Tile *currentTile);

    int getDistToAim(Tile* currentTile);
};


// creating a 'perfect' fractured maze, not-so-perfect when
// some walls or free spaces are there already
class perfectCreator : public tickInterface {
private:

    std::vector<std::vector<int> > visitable;

    Maze *maze;

    bool mazeSet = false;

    void initVec();

    void replaceEvery(int oldNum, int newNum);

    void out(std::string msg) {
        std::cout << "perfCreator: " + msg << std::endl;
    }

    bool areAllConnected();

    bool areDirectlyConnected(int x, int y, int dir);

public:

    void setMaze(Maze *maze);

    bool start();

    void connect(int X, int Y, int dir);

    void mazeChanged();

    void doTick();

    void ResetMaze();

};



#endif