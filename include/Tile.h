#ifndef TILE_H
#define TILE_H

using namespace std;
using namespace sf;

class Tile
{
    public:
        Tile(int x, int y, int height, int width);
        virtual ~Tile();
        bool isWall(int dir);
        void drawTile(RenderWindow *renderWind);
    protected:
    private:
        int locX = -1, locY = -1, scent1 = 0, scent2 = 0, height = -1, width = -1;
        // array<bool, 4> walls = {false, false, false, false};
        // RectangleShape rect();

};

#endif // TILE_H
