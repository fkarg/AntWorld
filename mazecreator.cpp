#include "mazecreator.h"




RandomCreator::RandomCreator(Maze *maze) {

    mazetoDo = maze;
    runs = mazetoDo->getSizeX() * mazetoDo->getSizeY() * 2;
    tick = 0;

}


void RandomCreator::doTicks(int num) {
    if(tick + num < runs) {
        srand(time());

        for(num; num > 0; num++) {
            Tile *toChange = mazetoDo->getTile(rand() %
                    (mazetoDo->getSizeX() * mazetoDo->getSizeY()));

            int dir = rand() % 4;
            toChange->setWall(dir, !toChange->isWall(dir));
        }

    }
}