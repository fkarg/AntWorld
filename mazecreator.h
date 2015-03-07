#ifndef MAZECREATOR_H
#define MAZECREATOR_H

#include "maze.hpp"
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include "ticksystem.h"



class RandomCreator : public tickInterface {
private:
    int runs = -1, tick = -1;   // how many ticks it should go on,
                                // and how many have already happened

    Maze *mazetoDo;             // the maze to be modified

public:
    RandomCreator(Maze *maze);
    void doTicks(int num = 1);
    void reset();
    void doTick();
};



// testing if there is a connection between two tiles
class Craver : public tickInterface {
private:
    int searchIndex = 0, searchDir = 0, withoutFound = 0;
    bool startSet = false, aimSet = false, mazeSet = false;
    Tile *startTile = NULL, *aimTile = NULL;
    Maze *maze = NULL;
    vector<vector<int> > visited;

    void initVec();

public:
    void setStart(Tile *startTile);
    void setAim(Tile *aimTile);
    void setMaze(Maze *maze);

    bool connected();

    Tile *getDirectlyConnected(Tile *check);

    void setVisited(int Index, int state);

    int searchForState1();
    int testForConnected(int index);

    void doTick();

};





#endif