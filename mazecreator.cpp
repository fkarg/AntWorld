#include "mazecreator.h"



// changing the maze to the @param maze
void RandomCreator::setMaze(Maze *maze) {

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

            std::cout << "Index: " << std::to_string(toChange->getIndex() ) <<
                    " dir: " << std::to_string(dir) << std::endl;

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



void RandomCreator::complete() {
    while (tick < runs) {
        doTicks();
    }
}








// Coloring all the Tiles in the @param std::vector tiles, and the start and aimTile
void Craver::ColorTiles(std::vector<Tile*> tiles) {
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

    out("StartTile set: " + std::to_string(startTile->getIndex() ) );
}


// setting the @param aimTile as tile to end
void Craver::setAim(Tile *aimTile) {
    Craver::aimTile = aimTile;
    aimSet = true;

    out("AimTile set: " + std::to_string(aimTile->getIndex() ) );
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
    if (startTile == aimTile) {
        startTile->setColor(sf::Color::White);
        return true;
    }

    int index = 0, length = 0;

    std::vector<std::vector<Tile*> > allPaths;

    std::vector<Tile*> currentPath;

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
                + std::to_string(currentTile->getIndex()));

        int actDir = rand() % 4;

        for (int dir = 0; dir < 4; dir++) {
            actDir++;
            actDir %= 4;
            Tile *testTile = currentTile->getSurrounding(actDir);
            if (testTile != NULL && !currentTile->isWall(actDir)) {
                if (testTile == aimTile) {
                    out("INFO: found aimTile!");
                    if (currentModified)
                        currentPath.erase(currentPath.end() - 1);
                    ColorTiles(currentPath);
                    return true;
                }

                if (!currentModified &&
                        !alreadyIncluded(currentPath, testTile)) {
                    currentPath.push_back(testTile);
                    currentModified = true;
                    out("Tile added, index: " + std::to_string(testTile->getIndex())
                            + ", actDir: " + std::to_string(actDir));
                } else if (!alreadyIncluded(currentPath, testTile)) {
                    allPaths.push_back(currentPath);
                    currentPath.erase(currentPath.end() - 1);
                    currentPath.push_back(testTile);
                    out("Tile " + std::to_string(testTile->getIndex()) + " added, "
                            "actDir: " + std::to_string(actDir));
                }
            }
        }

        out("updating currentPath ...\n");
        allPaths.erase(allPaths.begin() + index);
        if (currentModified)
            allPaths.push_back(currentPath);
    }

    out("INFO: couldn't find aimTile");
    startTile->setColor(sf::Color::Yellow);
    aimTile->setColor(sf::Color::Red);

    return false;
}



// returning the shortest path between all paths
// not needed anymore, since new ones are being pushed on the end
int Craver::IndexOfClosestToTile(std::vector<std::vector<Tile *> > allPaths) {

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

    out("shortestIndex: " + std::to_string(shortestIndex)
            + ", with length: " + std::to_string(shortestLength));

    return shortestIndex;

}




// returns if the currentTile is getting closer to the aimTile
// only needed for bigger fields without any walls
bool Craver::alreadyIncluded(std::vector<Tile*> path, Tile *currentAim) {

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

















// seeding the random and giving the std::vector it's size and initializing the values
void perfectCreator::initVec() {

    srand((unsigned int) time(0));

    if (mazeSet) {

        visitable = std::vector<std::vector<int> >( (unsigned long) maze->getSizeX(),
                std::vector<int>( (unsigned long) maze->getSizeY()) );

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


// tests if all tiles are connected already
bool perfectCreator::areAllConnected() {
    int start = visitable[0][0];

    for(int i = 0; i < maze->getSizeX(); i++) {
        for (int j = 0; j < maze->getSizeY(); j++) {
            if (visitable[i][j] != start)
                return false;
        }
    }

    return true;
}


// returns if two tiles are directly connected
bool perfectCreator::areDirectlyConnected(int x, int y, int dir) {
    if (maze->getTile(x, y)->isSurrounding(dir) )
        return !maze->getTile(x, y)->isWall(dir);
    return false;
}


// setting the @param maze and initializing the std::vector
void perfectCreator::setMaze(Maze *maze) {
    out("Maze set");
    perfectCreator::maze = maze;
    mazeSet = true;
}


// starting the perfectCreator and letting it run once over
// 'about' every tile and then again over every single one
// resulting in a definite perfect maze
bool perfectCreator::start() {

    out("start");

    if(!mazeSet)
        return false;

    mazeChanged();

    int Xstart, Ystart, dir;

    out("setting vars");

    for(int p = 0; p < maze->getSizeY() * maze->getSizeX() * 2; p++) {
        Xstart = rand() % maze->getSizeX();
        Ystart = rand() % maze->getSizeY();
        dir = rand() % 4;

        out("connecting x: " + std::to_string(Xstart) + ", y: " + std::to_string(Ystart)
                + ", dir: " + std::to_string(dir));

        connect(Xstart, Ystart, dir);
    }

    do {

        for (int i = 0; i < maze->getSizeX(); i++) {
            for (int j = 0; j < maze->getSizeY(); j++) {
                dir = rand() % 4;
                connect(i, j, dir);
            }
        }

    } while (!areAllConnected() );

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

        out("curNum: " + std::to_string(currentNum) + ", othNum: " + std::to_string(otherNum));

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



// reading in the state of the current maze and giving it it's 'visitable' values
void perfectCreator::mazeChanged() {
    initVec();
    for (int i = 0; i < maze->getSizeX(); i++) {
        for (int j = 0; j < maze->getSizeY(); j++) {
            if (areDirectlyConnected(i, j, 1) ) {
                if (visitable[i][j] > visitable[i + 1][j])
                    replaceEvery(visitable[i][j], visitable[i + 1][j]);
                else if (visitable[i][j] < visitable[i + 1][j])
                    replaceEvery(visitable[i + 1][j], visitable[i][j]);
            }

            if (areDirectlyConnected(i, j, 2) ) {
                if (visitable[i][j] > visitable[i][j + 1])
                    replaceEvery(visitable[i][j], visitable[i][j + 1]);
                else if (visitable[i][j] < visitable[i][j + 1])
                    replaceEvery(visitable[i][j + 1], visitable[i][j]);
            }
            out("Added x: " + std::to_string(i) + ", y: " + std::to_string(j) + ", num: "
                    + std::to_string(visitable[i][j]));
        }
    }
}




void perfectCreator::doTick() {
    // for implementations sake ...
}



// resetting the maze
void perfectCreator::ResetMaze() {

    for (int i = 0; i < maze->getSizeX(); i++) {
        for (int j = 0; j < maze->getSizeY(); j++) {
            for (int dir = 0; dir < 4; dir++)
                maze->getTile(i, j)->setWall(dir, true);
            maze->getTile(i, j)->setColor(sf::Color::Blue);
        }
    }

    std::cout << "Maze is reset" << std::endl;

}