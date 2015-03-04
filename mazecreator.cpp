#include "mazecreator.h"




RandomCreator::RandomCreator(Maze *maze) {

    mazetoDo = maze;
    runs = mazetoDo->getSizeX() * mazetoDo->getSizeY() * 2;
    tick = 0;

}


void RandomCreator::doTicks(int num = 1) {
    if(tick + num <= runs) {
        srand((unsigned int) time(0));

        for(num; num > 0; num--) {
            Tile *toChange = mazetoDo->getTile(rand() %
                    (mazetoDo->getSizeX() * mazetoDo->getSizeY()));

            int dir = rand() % 4;

            std::cout << "Index: " << std::to_string(toChange->getIndex() ) <<
                    "\n dir: " << std::to_string(dir) << std::endl << std::endl;

            toChange->setWall(dir, !toChange->isWall(dir));
            if(toChange->getSurrounding(dir) != 0)
                toChange->getSurrounding(dir)->setWall( (dir + 2) % 4,
                        !(toChange->getSurrounding(dir)->isWall(dir + 2 % 4) ) );
        }

    }
}