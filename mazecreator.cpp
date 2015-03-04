#include "mazecreator.h"




RandomCreator::RandomCreator(Maze *maze) {

    mazetoDo = maze;
    runs = mazetoDo->getSizeX() * mazetoDo->getSizeY() * 2;
    tick = runs;

    srand((unsigned int) time(0));

    std::cout << "Runs: " << std::to_string(runs) << std::endl;

}


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


void RandomCreator::reset() {
    tick = 0;
}