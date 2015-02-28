#ifndef MAZECREATOR_HPP
#define MAZECREATOR_HPP

#include "maze.hpp"
#include <ctime>
#include <cstdlib>
#include <math.h>

#include <iostream>
#include <string.h>
#include <strings.h>

using namespace std;

class Status {

private:
    int index = 0, dist = 0, distX = 2, distY = 1, x = -1, y = -1, state = -1;
    bool set = false;

public:

    Status(){}

    bool isSet() const {
        return set;
    }

    void setAll(int index, int dist, int distX, int distY, int x, int y, int state) {
        Status::index = index;
        Status::dist = dist;
        Status::distX = distX;
        Status::distY = distY;
        Status::x = x;
        Status::y = y;
        Status::state = state;
        set = true;
    }

    void update(int index, int dist, int distX, int distY) {
        Status::index = index;
        Status::dist = dist;
        Status::distX = distX;
        Status::distY = distY;
    }

    int getIndex() const {
        if (set)
            return index;
        return -1;
    }

    int getDist() const {
        if (set)
            return dist;
        return -1;
    }

    void setDist(int dist) {
        Status::dist = dist;
    }

    int getDistX() const {
        if (set)
            return distX;
        return -1;
    }

    void setDistX(int distX) {
        Status::distX = distX;
    }

    int getDistY() const {
        if (set)
            return distY;
        return -1;
    }

    void setDistY(int distY) {
        Status::distY = distY;
    }

    int getX() const {
        if (set)
            return x;
        return -1;
    }

    void setX(int x) {
        Status::x = x;
    }

    int getY() const {
        if (set)
            return y;
        return -1;
    }

    void setY(int y) {
        Status::y = y;
    }

    int getState() const {
        if (set)
            return state;
        return -1;
    }

    void setState(int state) {
        Status::state = state;
    }

    void setSet(bool set) {
        Status::set = set;
    }
};



class MazeCreator {
private:
    // the maze to be edited
    Maze *maze;

    // one map for all the states of the tiles from the maze
    vector<vector<int> > states;

    // the sizeX and sizeY of the Maze (needed!)
    int sizeX = -1, sizeY = -1, Xstart = -1, Ystart = -1;

    Status status;

    // setting the seed for rnd-num-gen
    void setSeed (unsigned int seed = (unsigned int) time(0) ) {
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
        // cout << "Prim's: " << message << endl;
    }

public:

    MazeCreator() {
        // ctr
        setSeed();
    }

    // setting the @param maze1: Maze
    void setMaze (Maze *maze1 ) {

        maze = maze1;
        sizeX = maze->getSizeX();
        sizeY = maze->getSizeY();
        states = vector<vector<int> >( (unsigned int)sizeX,
                vector<int>( (unsigned int) sizeY) );

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
        states[Xstart][Ystart] = 2;
    }

    // searching for an @param state: and returns it if there is one left,
    // @param resume: if the saved state of the Algorithm should be resumed
    // @param x: xstart and @param y: ystart are optional
    Tile *searchForState (int state, bool resume = false, int x = rand(), int y = rand() ) {
        x %= sizeX;
        y %= sizeY;

        out("Start set - x: " + to_string(x) + " y: " + to_string(y));

        int index = 0, dist = 0, distX = 2, distY = 1;
        if (testStates(x, y, state))
            return maze->getTile(x, y);
        index++;

        out("saving status");

        // testing if it should resume or not, and is either loading
        // or saving depending on @param resume
        if (!resume)
            status.setSet(false);
        if (!status.isSet() )
            status.setAll(index, dist, distX, distY, x, y, state);
        else if (resume) {
            index = status.getIndex();
            dist = status.getDist();
            distX = status.getDistX();
            distY = status.getDistY();
            x = status.getX();
            y = status.getY();
        }

        out("status set");

        while (dist <= sizeX + sizeY) {

            if (isLine(index)) {
                out("isLine, index: " + to_string(index));
                switch (index % 4) {
                    case 1:
                        dist++;
                        if (testStates(x, y - dist, state) )
                            return maze->getTile(x, y - dist);
                        break;
                    case 2:
                        if (testStates(x - dist, y, state) )
                            return maze->getTile(x - dist, y);
                        break;
                    case 3:
                        if (testStates(x, y + dist, state) )
                            return maze->getTile(x, y + dist);
                        break;
                    case 0:
                        if (testStates(x + dist, y, state) )
                            return maze->getTile(x + dist, y);
                        break;
                    default:
                        return NULL;
                }
            } else {
                out("isNot, index: " + to_string(index));

                if (index % 2 == 1) {
                    distX--;

                    if (distX == 0)
                        distX--;

                    if (distX == -dist)
                        distX = dist - 1;

                    distY = (int) (dist - sqrt(distX * distX));

                    if (distY == 0)
                        distY = 1;

                } else
                    distY = -distY;

                if (testStates(x + distX, y + distY, state) )
                    return maze->getTile(x + distX, y + distY);
            }

            index++;

            // updating the algorithms status
            status.update(index, dist, distX, distY);
            out("status updated");
        }

        return NULL;

    }


    // initiating Prim's Algorithm
    void PrimsAlgorithm() {
        out("Gonna search from the start ...");

        Tile* startTile = searchForState(2);

        if (startTile != NULL) {

            int startX = startTile->getIndex() % maze->getSizeX(),
                    startY = startTile->getIndex() / maze->getSizeY();

            setSurroundingState1(startX, startY);


            for (Tile *tile = searchForState(1, false, startX, startY );
                  tile != NULL; tile = searchForState(1, true)) {
                // ...
                int X = startTile->getIndex() % maze->getSizeX(),
                        Y = startTile->getIndex() / maze->getSizeY();

                states[X][Y] = 2;

                setSurroundingState1(X, Y);


                connectTiles(tile, searchSurrounding2(X, Y) );



            }
        }
    }

    // connecting two Tiles if they are next to each other
    void connectTiles(Tile *tile1, Tile *tile2) {
        if (tile1 != NULL && tile2 != NULL) {
            int dir = getDirOfTiles(tile1, tile2);
            if (dir != -1) {
                tile1->setWall(dir, false);
                tile2->setWall(dir + 2 % 4, false);
            }
        }
    }

    // returns the relational direction of the @param tile1 to @param tile2
    int getDirOfTiles(Tile *tile1, Tile *tile2) {

        if (tile1 == NULL || tile2 == NULL)
            return -1;

        if (tile1->getSurrounding(0) == tile2 && tile2->getSurrounding(2) == tile1)
            return 0;
        if (tile1->getSurrounding(1) == tile2 && tile2->getSurrounding(3) == tile1)
            return 1;
        if (tile1->getSurrounding(2) == tile2 && tile2->getSurrounding(0) == tile1)
            return 2;
        if (tile1->getSurrounding(3) == tile2 && tile2->getSurrounding(1) == tile1)
            return 3;
        return -1;
    }

    // searches for a Tile that has the state 2 also and returns it, else returns NULL
    Tile *searchSurrounding2 (int x, int y, int rec = 0) {

        if (rec > 30)
            return NULL;

        switch (rand() % 4) {
            case 0:
                return testStates(x, y - 1, 2) ?
                        maze->getTile(x, y - 1) : searchSurrounding2(x, y, rec + 1);
            case 1:
                return testStates(x - 1, y, 2) ?
                        maze->getTile(x - 1, y) : searchSurrounding2(x, y, rec + 1);
            case 2:
                return testStates(x, y + 1, 2) ?
                        maze->getTile(x, y + 1) : searchSurrounding2(x, y, rec + 1);
            case 3:
                return testStates(x + 1, y, 2) ?
                        maze->getTile(x + 1, y) : searchSurrounding2(x, y, rec + 1);
            default:
                return NULL;
        }

    };

    // setting the state of all the surrounding (if there are) tiles to 1
    void setSurroundingState1(int startX, int startY) {
        if (testStates( startX - 1, startY, 0) )
            states[startX - 1][startY] = 1;
        if (testStates( startX + 1, startY, 0) )
            states[startX + 1][startY] = 1;
        if (testStates( startX, startY - 1, 0) )
            states[startX][startY - 1] = 1;
        if (testStates( startX, startY + 1, 0) )
            states[startX][startY + 1] = 1;
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