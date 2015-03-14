#include "mazecreator.h"



// needs a @param: *maze: maze-pointer to get initialized
RandomCreator::RandomCreator(Maze *maze) {

    mazetoDo = maze;
    runs = mazetoDo->getSizeX() * mazetoDo->getSizeY() * 2;
    tick = runs;

    srand((unsigned int) time(0));

    std::cout << "Runs: " << std::to_string(runs) << std::endl;
}


// Does the @param num: specified number of ticks, if num > 0
// standard - param is 1
void RandomCreator::doTicks(int num) {
    if(tick + num <= runs) {
        for(num; num > 0; num--) {
            Tile *toChange = mazetoDo->getTile(rand() %
                    (mazetoDo->getSizeX() * mazetoDo->getSizeY()));

            int dir = rand() % 4;

            std::cout << "\nIndex: " << std::to_string(toChange->getIndex() ) <<
                    " dir: " << std::to_string(dir) << std::endl << std::endl;

            if(toChange->isSurrounding(dir) ) {
                toChange->setWall(dir, !toChange->isWall(dir));
                toChange->getSurrounding(dir)->setWall((dir + 2) % 4,
                        !toChange->getSurrounding(dir)->isWall( (dir + 2) % 4) );
            }

            tick++;
        }
    }
}


// resetting the tick-counter to randomize a new one
void RandomCreator::reset() {
    tick = 0;
}


// from the tickInterface, for polymorphism
void RandomCreator::doTick() {
    doTicks();
}










// Coloring all the Tiles in the @param vector tiles, and the start and aimTile
void Craver::ColorTiles(vector<Tile*> tiles) {
    for (int i = 0; i < tiles.size(); i++) {
        tiles[i]->setColor(colorTiles);
    }
    startTile->setColor(sf::Color::Yellow);
    aimTile->setColor(sf::Color::Green);
}


// setting the @param startTile as tile to start from
void Craver::setStart(Tile *startTile) {
    Craver::startTile = startTile;
    startSet = true;

    srand((unsigned int) time(0));

    out("StartTile set: " + to_string(startTile->getIndex() ) );
}


// setting the @param aimTile as tile to end
void Craver::setAim(Tile *aimTile) {
    Craver::aimTile = aimTile;
    aimSet = true;

    out("AimTile set: " + to_string(aimTile->getIndex() ) );
}


// setting the @param maze (necessary to get the size, etc. )
void Craver::setMaze(Maze *maze) {
    Craver::maze = maze;
    mazeSet = true;

    out("Maze set");
}



// coloring the path with @param color, if there is one
void Craver::colorPath(sf::Color color) {
    Craver::colorTiles = color;
    out("Color set");
}


void Craver::doTick() {
    // for overriding it ...
}






/*
 *
 *       A* search algorithm
 *
 * Before start:
 *  - setting the environment
 *  - setting the startTile
 *  - setting the aimTile
 *
 * THEN:
 *  - starting a path, including the startTile
 *  - adding every accessible tile to the path and creating a new one
 *      if necessary
 *  - not including it if it got included already (... Looops)
 *  - selecting the path currently shortest to the aimTile and looking for
 *      new tiles etc
 *  - deletion of dead ends
 *
 */




// searching with the A* search algorithm from the startTile onwards if the
// aimTile is reachable and if, showing it in the GUI
bool Craver::searchAStar() {

    if (!startSet || !aimSet || !mazeSet)
        return false;
    if (startTile == aimTile)
        return true;

    int index = 0, length = 0;

    vector<vector<Tile*> > allPaths;

    vector<Tile*> currentPath;

    Tile *currentTile = startTile;
    currentPath.push_back(currentTile);
    allPaths.push_back(currentPath);

    out("Craver started");

    while(allPaths.size() >= 1) {
        index = IndexOfClosestToTile(allPaths);
        currentPath = allPaths[index];
        length = (int) currentPath.size();
        length--;
        currentTile = currentPath[length];
        bool currentModified = false;

        out("Test at: " + std::to_string(index) + ", Tile Index: "
                + to_string(currentTile->getIndex() ) );

            for (int dir = 0; dir < 4; dir++) {
                Tile* testTile = currentTile->getSurrounding(dir);
                if (testTile != NULL && !currentTile->isWall(dir)) {
                    if (testTile == aimTile) {
                        out("INFO: found aimTile!");
                        if(currentModified)
                            currentPath.erase(currentPath.end() - 1);
                        ColorTiles(currentPath);
                        return true;
                    }

                    if (!currentModified &&
                            !alreadyIncluded(currentPath, testTile) ) {
                        currentPath.push_back(testTile);
                        currentModified = true;
                        out("Tile added, index: " + to_string(testTile->getIndex() )
                                + ", dir: " + to_string(dir) );
                    } else if (!alreadyIncluded(currentPath, testTile) ) {
                        allPaths.push_back(currentPath);
                        currentPath.erase(currentPath.end() - 1);
                        currentPath.push_back(testTile);
                        out("Tile " +  to_string(testTile->getIndex() ) + " added, "
                                "dir: " + to_string(dir) );
                    }
                }
            }

        out("updating currentPath ...\n");
        allPaths.erase(allPaths.begin() + index);
        if(currentModified)
            allPaths.push_back(currentPath);
    }

    return false;
}



// returning the shortest path between all paths
// not needed anymore, since new ones are being pushed on the end
int Craver::IndexOfClosestToTile(vector<vector<Tile *> > allPaths) {

    // return 0;

    int shortestLength =  getDistToAim(allPaths[0][allPaths[0].size() - 1]),
            shortestIndex = 0;

    for (int index = 0; index < allPaths.size(); index++) {
        int tmpDist = getDistToAim(allPaths[index][allPaths[index].size() - 1] );
        if (shortestLength > tmpDist ) {
            shortestLength = tmpDist;
            shortestIndex = index;
        }
    }

    out("shortestIndex: " + to_string(shortestIndex)
            + ", with length: " + to_string(shortestLength));

    return shortestIndex;

}




// returns if the currentTile is getting closer to the aimTile
// only needed for bigger fields without any walls
bool Craver::alreadyIncluded(vector<Tile*> path, Tile *currentAim) {

    for(int i = 0; i < path.size(); i++) {
        if (path[i] == currentAim)
            return true;
    }

    return false;
}


// returns the absolute distance from the @param currentTile to the aimTile
int Craver::getDistToAim(Tile *currentTile) {

    int aimX, aimY, currX, currY, aimInd, currInd;

    aimInd = aimTile->getIndex();
    aimX = aimInd / maze->getSizeX();
    aimY = aimInd % maze->getSizeY();

    currInd = currentTile->getIndex();
    currX = currInd / maze->getSizeX();
    currY = currInd % maze->getSizeY();

    return (int) (sqrt((currX - aimX) * (currX - aimX)) + sqrt((currY - aimY) * (currY - aimY)));
}

















// seeding the random and giving the vector it's size and initializing the values
void perfectCreator::initVec() {

    srand((unsigned int) time(0));

    if (mazeSet) {

        visitable = vector<vector<int> >( (unsigned long) maze->getSizeX(),
                vector<int>( (unsigned long) maze->getSizeY()) );
        for(int i = 0; i < maze->getSizeX(); i++) {
            for(int j = 0; j < maze->getSizeY(); j++) {
                visitable[i][j] = i * maze->getSizeX() + j + 1;
            }
        }
    }

}


// replacing every @param oldNum with the @param newNum
void perfectCreator::replaceEvery(int oldNum, int newNum) {
    for(int i = 0; i < maze->getSizeX(); i++) {
        for(int j = 0; j < maze->getSizeY(); j++) {
            if (visitable[i][j] == oldNum)
                visitable[i][j] = newNum;
        }
    }
}


// setting the @param maze and initializing the vector
void perfectCreator::setMaze(Maze *maze) {
    perfectCreator::maze = maze;
    mazeSet = true;
    initVec();
}


// starting the perfectCreator and letting it run once over
// 'about' every tile
bool perfectCreator::start() {

    out("start");

    if(!mazeSet)
        return false;

    int Xstart, Ystart, dir;

    out("setting vars");

    for(int p = 0; p < maze->getSizeY() * maze->getSizeX() * 2; p++) {
        Xstart = rand() % maze->getSizeX();
        Ystart = rand() % maze->getSizeY();
        dir = rand() % 4;

        out("connecting x: " + to_string(Xstart) + ", y: " + to_string(Ystart)
                + ", dir: " + to_string(dir));

        connect(Xstart, Ystart, dir);
    }

    for(int i = 0; i < maze->getSizeX(); i++) {
        for (int j = 0; j < maze->getSizeY(); j++) {
            dir = rand() % 4;
            connect(i, j, dir);
        }
    }


    // ...

    return true;
}



// connecting the tile at @param X and @param Y with the one in @param dir
// if the tile is not included already or there is no tile (...)
void perfectCreator::connect(int X, int Y, int dir) {

    int currentNum = visitable[X][Y], otherNum = -1;

    if(maze->getTile(X, Y)->isSurrounding(dir) ) {


        switch (dir) {
            case 0:
                otherNum = visitable[X][Y - 1];
                break;
            case 1:
                otherNum = visitable[X + 1][Y];
                break;
            case 2:
                otherNum = visitable[X][Y + 1];
                break;
            case 3:
                otherNum = visitable[X - 1][Y];
                break;
            default:
                break;
        }

        out("curNum: " + to_string(currentNum) + ", othNum: " + to_string(otherNum));

        if (currentNum != otherNum) {
            if (currentNum > otherNum) {
                replaceEvery(currentNum, otherNum);
            } else {
                replaceEvery(otherNum, currentNum);
            }
            maze->getTile(X, Y)->setWall(dir, false);
            maze->getTile(X, Y)->getSurrounding(dir)->setWall((dir + 2) % 4, false);
        }

    }

}




void perfectCreator::doTick() {
    // for implementations sake ...
}