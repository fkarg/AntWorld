#ifndef MAZECREATOR_HPP
#define MAZECREATOR_HPP



#include "maze.hpp"
#include <ctime>
#include <cstdlib>
#include <math.h>

#include <iostream>


using namespace std;



class MazeCreator {
private:
    // the maze to be edited
    Maze* maze;

    // one map 
    vector<vector<int> > states;

    // the sizeX and sizeY of the Maze (needed!)
    int sizeX = -1, sizeY = -1, Xstart = -1, Ystart = -1;

    // setting the seed for rnd-num-gen
    void setSeed (int seed = time(0) ) {
        srand(seed);
    }

    // included test if x and y are within the boundaries of the map
    bool testStates (int x, int y, int state) {
        if (x >= 0 && x < sizeX && y >= 0 && y < sizeY) {
            out("Let it through - x: " + to_string(x) + " y: " + to_string(y));
            if (states[x][y] == state) {
                out("Found something! x: " + to_string(x) + " y: " + to_string(y));
                return true;
            }
        }
        return false;
    }

    void out (string message) {
        cout << "Prim's: " << message << endl;
    }

public:

    MazeCreator(){
        // ctr
        setSeed();
    }

    // setting the @param maze1: Maze
    void setMaze (Maze* maze1 ) {
        maze = maze1;
        sizeX = maze->getSizeX();
        sizeY = maze->getSizeY();
        states = vector<vector<int> >(sizeX, vector<int>(sizeY) );

        for ( int i = 0; i < sizeX; i++ ) {
            for ( int j = 0; j < sizeY; j++ ) {
                states[i][j] = 0;
            }
        }

    }

    // setting a starting point or if not given, start at a random point
    void setStart (int startX = rand(), int startY = rand() ) {
        Xstart = startX % sizeX;
        Ystart = startY % sizeY;
        states[Xstart][Ystart] = 1;
    }

    // searching for an state1 if there is one left, 
    // returns the multiplied index or -1
    Tile* searchForState1 (int x = rand(), int y = rand() ) {
        x %= sizeX;
        y %= sizeY;

        out("Start set - x: " + to_string(x) + " y: " + to_string(y));

        int index = 0, dist = 0, distX = 2, distY = 1;
        if (testStates(x, y, 1))
            return maze->getTile(x, y);
        index++;
        while (index <= sizeX * sizeY * 2) {

            if (isLine(index)) {
                out("isLine, index: " + to_string(index));
                switch (index % 4) {
                    case 1:
                        dist++;
                        if (testStates(x, y - dist, 1) )
                            return maze->getTile(x, y - dist);
                        break;
                    case 2:
                        if (testStates(x - dist, y, 1) )
                            return maze->getTile(x - dist, y);
                        break;
                    case 3:
                        if (testStates(x, y + dist, 1) )
                            return maze->getTile(x, y + dist);
                        break;
                    case 0:
                        if (testStates(x + dist, y, 1) )
                            return maze->getTile(x + dist, y);
                        break;
                }
            } else {
                out("isNot, index: " + to_string(index));

                if (index % 2 == 1) {
                    distX--;

                    if (distX == 0)
                        distX--;

                    if (distX == -dist)
                        distX = dist - 1;

                    distY = dist - sqrt(distX * distX);

                    if (distY == 0)
                        distY = 1;

                } else
                    distY = -distY;

                if (testStates(x + distX, y + distY, 1) )
                    return maze->getTile(x + distX, y + distY);

            }

            index++;
        }
        return NULL;

    }

    // initiating Prim's Algorithm
    void PrimsAlgorithm () {
        out("Gonna search from the start ...");
        searchForState1()->setWall(3, false);
    }

    // returns if the @param ind: number is directly in horizontal or vertical direction
    bool isLine (int ind) {

        int start = 0;

        if (ind > 0 && ind <= 4)
            return true;

        for (int i = 0; i < sqrt(ind); i++) {
            start += i * 4 + 4;
            if (ind > start && ind <= start + 4)
                return true;
        }

        return false;
    }
};



#endif