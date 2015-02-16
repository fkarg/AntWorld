#ifndef MAZECREATOR_HPP
#define MAZECREATOR_HPP
#include "maze.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;


class MazeCreator{
private:
    // the maze to be "edited"
    Maze *maze;

    // a map of the same size as the maze, for the different states of the maze
    vector<vector<int> > state;
    int sizeX = -1, sizeY = -1;
    int x, y;
    void setSeed(int seed = time(0)){
        srand(seed);
    }
    // ...
protected:
    // ...
public:

    // ctr
    MazeCreator(){
    }

    // setting the @param maze1: Maze to be "edited", and initializing the state-map
    void setMaze(Maze* maze1){
        maze = maze1;
        sizeX = maze->getSizeX();
        sizeY = maze->getSizeY();
        state = vector< vector<int> >(sizeX, vector<int>(sizeY));
        for(int i = 0; i < sizeX; i++){
            for(int j = 0; j < sizeY; j++){
                state[i][j] = 0;
            }
        }
    }

    // A bad try of Prim's Algorithm. FIXME: TRY AGAIN!
    void PrimsAlgorithm(){
        cout << "inside Prim's" << endl;
        setSeed();
        int startX = 9, startY = 0;
        state[startX][startY] = 1;
        bool allVisited = false;

        cout << "starting while ..." << endl;

        int frame = 0;

        while(!allVisited){
            cout << "Phase: " << frame << endl;
            allVisited = !isState1();
        }
    }

    bool isState1(){
        for (int i = 0; i < sizeX; i++) {
            for(int j = 0; j < sizeY; j++){
                x = i;
                y = j;
                if (testState2())
                    state[x][y] = 2;
                if (state[x][y] == 1) {
                    int dir = lookforDir();
                    cout << "looked for dir ... " << dir << endl;
                    if (dir >= 0) {
                        Tile* tile = maze->getTile(x, y);
                        cout << "created tile ..." << endl;
                        tile->setWall(dir, false);
                        cout << "got tile" << endl;
                        tile->getSurrounding(dir)->setWall(dir + 2 % 4, false);
                        cout << "got surrounding tile" << endl;
                        switch(dir){
                            case 0:
                                state[x][y - 1] = 1;
                                break;
                            case 1:
                                state[x + 1][y] = 1;
                                break;
                            case 2:
                                state[x][y + 1] = 1;
                                break;
                            case 3:
                                state[x - 1][y] = 1;
                                break;
                        }
                    }
                }
            }
        }
    }


    int lookforDir(){
        if (x != 0 && x != sizeX && y != 0 && y != sizeY) {
            if(!testDir(0))
                return 0;
            if(!testDir(2))
                return 2;
            if(!testDir(1))
                return 1;
            if(!testDir(3))
                return 3;
        } else {
            if(x == 0 && y == 0) {
                if(!testDir(2))
                    return 2;
                if(!testDir(1))
                    return 1;
            }
            if(x == sizeX && y == 0){
                if(!testDir(2))
                    return 2;
                if(!testDir(3))
                    return 3;
            }
            if(x == sizeX && y == sizeY){
                if(!testDir(0))
                    return 0;
                if(!testDir(3))
                    return 3;
            }
            if(x == 0 && y == sizeY){
                if(!testDir(0))
                    return 0;
                if(!testDir(1))
                    return 1;
            }

            if(x == 0){
                if(!testDir(0))
                    return 0;
                if(!testDir(2))
                    return 2;
                if(!testDir(1))
                    return 1;
            }
            if(x == sizeX){
                if(!testDir(0))
                    return 0;
                if(!testDir(2))
                    return 2;
                if(!testDir(3))
                    return 3;
            }
            if(y == 0){
                if(!testDir(2))
                    return 2;
                if(!testDir(1))
                    return 1;
                if(!testDir(3))
                    return 3;
            }
            if(y == sizeY){
                if(!testDir(0))
                    return 0;
                if(!testDir(1))
                    return 1;
                if(!testDir(3))
                    return 3;
            }
        }
        return -1;
    }


    bool testState2(){
        if (x != 0 && x != sizeX && y != 0 && y != sizeY) {
            return testDir(1) && testDir(3) && testDir(2) && testDir(0);
        } else {
            if(x == 0 && y == 0)
                return testDir(1) && testDir(2);
            if(x == sizeX && y == 0)
                return testDir(2) && testDir(3);
            if(x == sizeX && y == sizeY)
                return testDir(3) && testDir(0);
            if(x == 0 && y == sizeY)
                return testDir(0) && testDir(1);

            if(x == 0)
                return testDir(1) && testDir(2) && testDir(0);
            if(x == sizeX)
                return testDir(3) && testDir(2) && testDir(0);
            if(y == 0)
                return testDir(1) && testDir(2) && testDir(3);
            if(y == sizeY)
                return testDir(0) && testDir(1) && testDir(3);
        }

    }

    bool testDir(int dir){
        switch(dir){
            case 0:
                return state[x][y - 1] >= 1;
            case 1:
                return state[x + 1][y] >= 1;
            case 2:
                return state[x][y + 1] >= 1;
            case 3:
                return state[x - 1][y] >= 1;
        }
    }

    // ...



};








#endif