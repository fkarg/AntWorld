#ifndef MAZECREATOR_H
#define MAZECREATOR_H

#include "maze.hpp"
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
    void doTicks(int num = 1);
    void reset();
    void doTick();
};



// testing if there is a connection between two tiles
class Craver : public tickInterface {
private:
    bool startSet = false, aimSet = false, mazeSet = false;
    Tile *startTile = NULL, *aimTile = NULL;
    Maze *maze = NULL;
    vector<vector<int> > visited;
    vector<int> visited2;

    sf::Color colorTiles = sf::Color(Color::Blue);

    void ColorTiles(vector<Tile*> tiles);

    void out(std::string msg) {
        cout << "Creator: " + msg << endl;
    }

public:
    void setStart(Tile *startTile);
    void setAim(Tile *aimTile);
    void setMaze(Maze *maze);

    void colorPath(sf::Color color);

    void doTick();

    // bool searchAStar(Tile *startTile = Craver::startTile,
    //         Tile *aimTile = Craver::aimTile, Maze *maze = Craver::maze);

    bool searchAStar();

    int IndexOfClosestToTile(vector<vector<Tile *> > allPaths);

    bool alreadyIncluded(vector<Tile*> path, Tile *currentTile);

    int getDistToAim(Tile* currentTile);
};





#endif