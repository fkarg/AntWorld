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
}


// setting the @param startTile as tile to start from
void Craver::setStart(Tile *startTile) {
    Craver::startTile = startTile;
    startSet = true;

    srand((unsigned int) time(0));
}


// setting the @param aimTile as tile to end
void Craver::setAim(Tile *aimTile) {
    Craver::aimTile = aimTile;
    aimSet = true;
}


// setting the @param maze (necessary to get the size etc
void Craver::setMaze(Maze *maze) {
    Craver::maze = maze;
    mazeSet = true;
}


// returns false if either the start, the aim or the aren't set yet
// returns true if the two tiles are the same or are connected
bool Craver::connected() {

    if (!startSet || !aimSet || !mazeSet)
        return false;

    if (startTile == aimTile)
        return true;

    vector<Tile*> accessible;

    accessible.push_back(startTile);

    initVec();

    setVisited(startTile->getIndex(), 2);

    bool added = true;

    while (added) {

        int state1Index = searchForState1();

        int newDir = -1;
        newDir = testForConnected(state1Index);

        int newIndex = -1;

        if (newDir >= 0)
            newIndex = maze->getTile(state1Index)->getSurrounding(newDir)->getIndex();

        if (newIndex >= 0 && newIndex <= maze->INDEX_MAX() ) {
            added = true;
            Tile *newTile = maze->getTile(newIndex);
            accessible.push_back(newTile);
            setVisited(newIndex, 1);
            if (newTile == aimTile)
                return true;
        } else
            added = false;


    }

    return false;
}



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




int Craver::searchForState1() {
    if (maze == NULL)
        return -1;

    for (int i = searchIndex / maze->getSizeX(); i < maze->getSizeX(); i++) {
        for (int j = searchIndex % maze->getSizeY(); j < maze->getSizeY(); j++) {
            if(visited[i][j] >= 1)
                return searchIndex;
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
            visited[index / maze->getSizeX()][index % maze->getSizeY() - 1] >= 1 )
        return 0;


    if(!maze->getTile(index)->isWall(1) &&
            visited[index / maze->getSizeX() + 1][index % maze->getSizeY()] >= 1 )
        return 1;


    if(!maze->getTile(index)->isWall(2) &&
            visited[index / maze->getSizeX()][index % maze->getSizeY() + 1] >= 1 )
        return 2;


    if(!maze->getTile(index)->isWall(3) &&
            visited[index / maze->getSizeX() - 1][index % maze->getSizeY()] >= 1 )
        return 3;

    return -1;

}



void Craver::doTick() {
    // for overriding it ...
    // TODO: doing the colouring while searching and 'pausing' the search
}






