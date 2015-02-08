#ifndef MAZE_H
#define MAZE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "Tile.h"

using namespace std;
using namespace sf;

class Maze
{
    public:
        Maze(int sizeX2, int sizeY2);
        virtual ~Maze();
        void drawMaze(RenderWindow *renderWind);
    protected:
    private:
        int sizeX = -1, sizeY = -1;

};

#endif // MAZE_H
