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
 * TODO: update comments
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








void perfectCreator::initVec() {
    visitable = vector<vector<bool> >( (unsigned long) maze->getSizeX(),
            vector<bool>( (unsigned long) maze->getSizeY()) );

    if (mazeSet) {
        for(int i = 0; i < maze->getSizeX(); i++) {
            for(int j = 0; j < maze->getSizeY(); j++) {
                visitable[i][j] = false;
            }
        }
    }
}



void perfectCreator::setMaze(Maze *maze) {
    perfectCreator::maze = maze;
    initVec();
    mazeSet = true;
    craver.setMaze(maze);
}



void perfectCreator::setStart(int x, int y) {
    visitable[x][y] = true;
    startX = x;
    startY = y;
    startSet = true;
}



bool perfectCreator::start() {
    if(!mazeSet || !startSet)
        return false;





    return false;
}




int perfectCreator::searchForClosest(bool state, int IndexFrom) {

    if (!mazeSet)
        return -1;

    int x = IndexFrom / maze->getSizeX(), y = IndexFrom % maze->getSizeY();




    return -1;
}




void perfectCreator::doTick() {
    // for implementations sake ...
}