#ifndef MAZE_H
#define MAZE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "tile.h"

using namespace std;
using namespace sf;

class Maze
{
    public:
        Maze(int sizeX, int sizeY);
        virtual ~Maze();
        void drawMaze(const RenderWindow& renderWind);
    protected:
    private:
        int sizeX, sizeY;

};

#endif // MAZE_H
