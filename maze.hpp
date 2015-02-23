#ifndef MAZE_HPP
#define MAZE_HPP

#include <iostream>

using namespace std;
using namespace sf;


/*
 * Tile: the background is out of tiles
 *
 * setSize:
 * @param x: X-location of the Tile later on
 * @param y: Y-location of the Tile later on
 * @param height2: the height of the tile
 * @param width2: the width of the tile
 * (the 2 is there since the scope resolution operator didn't work for some reason)
 * setting the size, position and color of the rect
 *
 *
 * drawTile:
 * @param renderWindow: the window the rect is drawn in
 * drawing the rect
 *
 * isWall:
 * @param dir: the direction, 0 = up, 1 = right, 2 = down, 3 = left
 */
class Tile {

private:
    int locX, locY, height, width, food = 0;

    bool wall[4] = { true, true, true, true };
//    the directions: up, right, down, left
//                     0 ,   1 ,   2 ,   3

    Tile* surrounding[4] = {}; // to direct an agent to the next one

    RectangleShape rect;
    RectangleShape Walls[4];

    // adding or actualizing the Walls positions
    void addWalls(){

        RectangleShape temp;
        temp.setFillColor(Color::Magenta);

        temp.setPosition(locX, locY);

        temp.setSize(Vector2f(width, 2));

        Walls[0] = temp;

        temp.setSize(Vector2f(2, height));

        Walls[3] = temp;

        temp.setPosition(locX + width - 2, locY);
        temp.setSize(Vector2f(2, height));

        Walls[1] = temp;

        temp.setPosition(locX, locY + height - 2);
        temp.setSize(Vector2f(width, 2));

        Walls[2] = temp;

    }

public:
    // setting the initial @param x: X and @param y: Y values,
    // as well as the height and width
    void setSize(int x, int y, int height2, int width2){
        locX = x;
        locY = y;
        height = height2;
        width = width2;

        addWalls();

        rect.setSize(Vector2f(height, width));
        rect.setFillColor(Color::Blue);
        rect.setPosition(Vector2f(locX, locY));
    }

    // Draws the Tile
    void drawTile(RenderWindow *renderWindow){
        renderWindow->draw(rect);
    }

    // Draws the Walls of the Tile
    void drawWalls(RenderWindow *renderWindow){
        for(int x = 0; x < 4; x++){
            if (wall[x]) {
                renderWindow->draw(Walls[x]);
            }
        }
    }

    // moving the rect for @param x: X and @param y: Y pixels ...
    void move(int x, int y){
        rect.move(Vector2f(x, y));
    }

    // returns if there is a wall at the @param dir: direction
    bool isWall(int dir){
        return wall[dir];
    }

    // returns the x value of the Tile
    int getX(){
        return locX;
    }

    // returns the y value of the Tile
    int getY(){
        return locY;
    }

    // returns any food if there is on this Tile, but max 10
    int getFood(){
        if(food >= 10){
            food -= 10;
            return 10;
        } else {
            int tmp = food;
            food = 0;
            return tmp;
        }
    }

    // returns the surrounding Tile at @param dir: direction
    Tile* getSurrounding(int dir){
        return surrounding[dir];
    }

    // returns if there is something in this Direction (a tile)
    bool isSurrounding(int dir){
        return surrounding[dir] != NULL;
    }

    // sets the @param *tile: Tile next to it in @param dir: direction
    void setSurrounding(int dir, Tile *tile){
        surrounding[dir] = tile;
    }

    // setting the wall of @param dir: direction at @param setWall.
    void setWall(int dir, bool setWall){
        cout << "in setWall " << endl;
        cout << " newWallstate: " << endl;
        cout << std::noboolalpha << setWall << endl;
        cout << " oldWallstate: " << endl;
        cout << std::noboolalpha << wall[dir] << endl;
        cout << " dir: " << endl;
        cout << to_string(dir) << endl;
        wall[dir] = setWall;
        cout << "after setWall" << endl;
    }

};






/*
 * Maze: including all the Tiles, used to manipulate only specific Tiles
 * @param xSize: how many tiles are gonna be in x direction
 * @param ySize: how many tiles are gonna be in y direction
 * creating a Maze with with xSize x ySize Tiles
 *
 * drawMaze:
 * @param renderWindow: needed for the Tile.drawTile method to draw on
 * drawing all Tiles in the MAP
 */
class Maze {

private:
    int sizeX = -1, sizeY = -1;
    vector<vector<Tile> > MAP;

public:
    // creating the Maze with @param xSize times @param ySize Tiles
    Maze(int xSize, int ySize){
        sizeX = xSize;
        sizeY = ySize;
        MAP = vector< vector<Tile> >(xSize, vector<Tile>(ySize));
        for(int i = 0; i < xSize; i++){
            for(int j = 0; j < ySize; j++){
                Tile tile;
                tile.setSize(i * 31, j * 31, 30, 30);
                MAP[i][j] = tile;
            }
        }
        setNeighbourTiles();
    }

    // setting the surrounding - variable
    void setNeighbourTiles(){
        for(int i = 0; i < sizeX; i++){
            for(int j = 0; j < sizeY; j++){
                if (j > 0)
                    MAP[i][j].setSurrounding(0, &MAP[i][j - 1]);

                if (i < sizeX - 1)
                    MAP[i][j].setSurrounding(1, &MAP[i + 1][j]);

                if(j < sizeY - 1)
                    MAP[i][j].setSurrounding(2, &MAP[i][j + 1]);

                if(i > 0)
                    MAP[i][j].setSurrounding(3, &MAP[i - 1][j]);
            }
        }
    }

    // drawing the Maze on the @param renderWindow
    void drawMaze(RenderWindow *renderWindow){
        for(int i = 0; i < sizeX; i++){
            for(int j = 0; j < sizeY; j++){
                MAP[i][j].drawTile(renderWindow);
                MAP[i][j].drawWalls(renderWindow);
            }
        }
    }

    // moving the whole maze for @param x: X and @param y: Y pixels
    void move(int x, int y){
        for(int i = 0; i < sizeX; i++){
            for(int j = 0; j < sizeY; j++){
                MAP[i][j].move(x, y);
            }
        }
    }

    // returning a tile at a specific location
    Tile* getTile(int i, int j){
        if(i > 0 && i < sizeX && j > 0 && j < sizeY)
            return &MAP[i][j];
    }

    // returning the sizeX of the Maze
    int getSizeX(){
        return sizeX;
    }

    // returning the sizeY of the Maze
    int getSizeY(){
        return sizeY;
    }
};

#endif
