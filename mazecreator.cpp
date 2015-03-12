#include <string.h>
#include <strings.h>
#include "mazecreator.h"


/*
 * Idee: falls nicht anders lösbar: vector mit 'schon bekannten' komplett visiteden
 *
 * oder: verschiedene states mit dem aktuellen vector
 */




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











// initializing the 'visited' vector in it's size to 0
void Craver::initVec() {
    visited = vector<vector<int> >(
            (unsigned long) maze->getSizeX(),
            vector<int>((unsigned long) maze->getSizeY()) );

    for (int i = 0; i < maze->getSizeX(); i++) {
        for (int j = 0; j < maze->getSizeY(); j++) {
            visited[i][j] = 0;
        }
    }

    visited2 = vector<int>((unsigned long) maze->INDEX_MAX() );
    for (int i = 0; i < maze->INDEX_MAX(); i++ ) {
        visited2[i] = 0;
    }
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


// returns false if either the start, the aim or the aren't set yet
// returns true if the two tiles are the same or are connected
bool Craver::connected() {

    if (!startSet || !aimSet || !mazeSet)
        return false;

    cout << "start: " << startTile << " aim: " << aimTile << endl;

    if ( (void*) startTile == (void*) aimTile) {
        out("StartTile and AimTile are Equal");
        return true;
    }

    out("Testing ...");

    vector<Tile*> accessible;

    accessible.push_back(startTile);

    initVec();

    setVisited(startTile->getIndex(), 2);

    bool added = true;

    while (added) {

        int state1Index = searchForState1();

        int newDir = testForConnected(state1Index);

        int newIndex = -1;

        if (newDir >= 0)
            newIndex = maze->getTile(state1Index)->getSurrounding(newDir)->getIndex();

        out("state1Index: " + std::to_string(state1Index)
                + ", newDir: " + std::to_string(newDir)
                + ", newIndex: " + std::to_string(newIndex) );

        if (newIndex >= 0 && newIndex <= maze->INDEX_MAX() ) {
            added = true;
            Tile *newTile = maze->getTile(newIndex);

            out("Comparing: " + std::to_string(newTile->getIndex() ) );

            accessible.push_back(newTile);
            setVisited(newIndex, 1);
            if ( aimTile == newTile ) {
                ColorTiles(accessible);
                out("INFO:     Found AimTile");
                return true;
            }

            out("currentTile != AimTile");

        } else
            added = false;
    }

    return false;
}


// setting visited at @param Index to @param state
void Craver::setVisited(int Index, int state) {
    visited[Index / maze->getSizeX()][Index % maze->getSizeY()] = state;
}



// returns either a directly connected tile or NULL
// or rather, returns a pointer to the first tile in the array,
// there are still tiles after that FIXME: unused memory allocation?
Tile *Craver::getDirectlyConnected(Tile *check) {

    Tile *surrounds[4] = {NULL, NULL, NULL, NULL};

    for (int dir = 0; dir < 4; dir++) {
        if (check->isSurrounding(dir) && !check->isWall(dir) )
            surrounds[dir] = check->getSurrounding(dir);
    }

    return surrounds[0];
}



// searching for a state1,
int Craver::searchForState1() {
    if (maze == NULL)
        return -1;

    for (int i = searchIndex / maze->getSizeX(); i < maze->getSizeX(); i++) {
        for (int j = searchIndex % maze->getSizeY(); j < maze->getSizeY(); j++) {
            if(visited[i][j] >= 1)
                return searchIndex;

            cout << "Index: " + to_string(searchIndex) + ", visited: "
                    + to_string(visited[i][j]) << endl;

            searchIndex++;
        }
    }

    searchIndex = 0;
    return searchForState1();
}


// Testing if there possibly is a tile with connection to
// one that is not visited yet
int Craver::testForConnected(int index) {

    if(!maze->getTile(index)->isWall(0) &&
            visited[index / maze->getSizeX()][index % maze->getSizeY() - 1] < 1 )
        return 0;


    if(!maze->getTile(index)->isWall(1) &&
            visited[index / maze->getSizeX() + 1][index % maze->getSizeY()] < 1 )
        return 1;


    if(!maze->getTile(index)->isWall(2) &&
            visited[index / maze->getSizeX()][index % maze->getSizeY() + 1] < 1 )
        return 2;


    if(!maze->getTile(index)->isWall(3) &&
            visited[index / maze->getSizeX() - 1][index % maze->getSizeY()] < 1 )
        return 3;

    return -1;

}



// coloring the path with @param color, if there is one
void Craver::colorPath(sf::Color color) {
    Craver::colorTiles = color;
    out("Color set");
}


void Craver::doTick() {
    // for overriding it ...
    // TODO: doing the colouring while searching and 'pausing' the search
}






/*
 * Idea: setting a startTile and a aimTile, a maze for all necessary size allocations (needed?)
 * then: searching from the startTile to every accessible tile from there if it is the aimTile
 * states: tiles accessible, and all tiles around them are already included -> 2
 * states: tiles accessible, but there are tiles around them not yet included -> 1
 * states: tiles not yet accessed or not even connected to the startTile -> 0
 *
 * either with one states-Array or with several lists of Tile*
 *
 * with states-Array needed functions and methods:
 *  - find a tile that is not yet fully connected
 *  - testing if tiles are fully connected already
 *  - setting tiles fully connected
 *  - searching for tiles next to them not fully connected
 *  - (searching the closest to the startTile) Academical correct way
 *  - Information about distance to the startTile -> two state-Arrays?
 *  - If found, information if the tile is on the currently shortest path
 *
 *  - somewhat 'nodes' - Tiles
 *  - dynamic multidimensional arrays
 *  - searching for a 'ongoing' node
 *  - removing dead ends? - Affirmitive
 *  - what to do with crossing paths?
 *  - what to do with loops?
 *  - a 'visited' thing is necessary
 *
 *
 * with lists of Tile* needed:
 *  - dynamic array of lists of Tile*, each indicating a path
 *  - solvable with a dynamic array of connected Tiles
 *  - when more than one free connectible tile -> copying path and splitting from then forth
 *  - what to do when two ways are of equal length? return the one first found?
 *  - some tiles are accessible several times, exclude them?
 *  - some tiles might lead to a dead end, delete those paths?
 *  - if a path is found, search for another one?
 *  - returning the whole path or only if it is accessible?
 *  - DIFFERENT NODE SYSTEM?
 *
 */





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
        index = IndexOfShortestPath(allPaths);
        currentPath = allPaths[index];
        length = (int) currentPath.size();
        length--;
        currentTile = currentPath[length];
        bool currentModified = false;

        out("Test at: " + std::to_string(index) + ", Tile Index: "
                + to_string(currentTile->getIndex() ) );

        if (gettingCloser(currentTile, length) ) {

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

                    if (testTile != currentPath[length - 1] && !currentModified) {
                        currentPath.push_back(testTile);
                        currentModified = true;
                        out("Tile added, index: " + to_string(testTile->getIndex() )
                                + ", dir: " + to_string(dir) );
                    } else if (testTile != currentPath[length - 2] &&
                            testTile != currentPath[length] &&
                            testTile != currentPath[length - 1]) {
                        allPaths.push_back(currentPath);
                        currentPath.erase(currentPath.end() - 1);
                        currentPath.push_back(testTile);
                        out("Tile " +  to_string(testTile->getIndex() ) + " added, "
                                "dir: " + to_string(dir + 1) );
                    }
                }
            }
        }

        out("updating currentPath ...\n");
        allPaths.erase(allPaths.begin() + index);
        if(currentModified)
            allPaths.push_back(currentPath);
    }

    return true;
}




int Craver::IndexOfShortestPath(vector<vector<Tile *> > allPaths) {

    // int shortestLength = (int) allPaths[0].size(), shortestIndex = 0;
//
    // for (int index = 0; index < allPaths.size(); index++) {
//
    //     if (shortestLength > allPaths[index].size() ) {
    //         shortestLength = (int) allPaths[index].size();
    //         shortestIndex = index;
    //     }
    // }
//
    // out("shortestIndex: " + to_string(shortestIndex)
    //         + ", with length: " + to_string(shortestLength));
//
    // return shortestIndex;

    return 0;
}





bool Craver::gettingCloser(Tile * currentTile, int pathLength) {
    int aimX, aimY, currX, currY, startX, startY, aimInd, currInd, startInd;

    aimInd = aimTile->getIndex();
    aimX = aimInd / maze->getSizeX();
    aimY = aimInd % maze->getSizeY();

    currInd = currentTile->getIndex();
    currX = currInd / maze->getSizeX();
    currY = currInd % maze->getSizeY();

    startInd = startTile->getIndex();
    startX = startInd / maze->getSizeX();
    startY = startInd % maze->getSizeY();

    int dist = (int) (sqrt((currX - aimX) * (currX - aimX))
            + sqrt((currY - aimY) * (currY - aimY)));

    int TotalDist = (int) (sqrt((startX - aimX) * (startX - aimX))
            + sqrt((startY - aimY) * (startY - aimY)));

    out("aimInd: " + to_string(aimInd) + ", currInd: " + to_string(currInd)
            + ", startInd: " + to_string(startInd)
            + ", dist: " + to_string(dist) + ", length: " + to_string(pathLength)
            + ", totalDist: " + to_string(TotalDist) );

    // return ( (currX + 2 + dist >= aimX && currX - 2 + dist <= aimX)
    //         || (currX + 2 - dist >= aimX && currX - 2 - dist <= aimX) )
    //         && ( (currY + 2 + dist >= aimY && currY - 2 + dist <= aimY)
    //         || (currY + 2 - dist >= aimY && currY - 2 - dist <= aimY) );


    // (currX - aimX) + 2 >= dist
    // (currY - aimY) - 2 <= dist
    // (aimX - currX) + 2 >= dist
    // (aimY - currY) - 2 <= dist


    // return dist + pathLength + 1 >= TotalDist && dist + pathLength - 1 <= TotalDist;
    return dist + pathLength == TotalDist;

}


