#ifndef MAZE_HPP
#define MAZE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

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
 * setting the size, position and color of the rect
 *
 * setIndex:
 * @param index: setting the index of the tile, needed for displaying
 */
class Tile {

protected:
    int locX, locY, height, width, food = 0, index = -1;

    bool wall[4] = { true, true, true, true };
//    the directions: up, right, down, left
//                     0 ,   1 ,   2 ,   3

    Tile *surrounding[4] = {}; // to direct an agent to the next one

    // RectangleShapes to draw the tile ad the walls later on
    RectangleShape rect;
    RectangleShape Walls[4];

    // adding or actualizing the Walls positions
    void addWalls() {

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

    Tile(){
        // ctr
    }

    // setting the initial @param x: X and @param y: Y values,
    // as well as the height and width
    void setSize(int x, int y, int height2, int width2) {
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
    void drawTile(RenderWindow *renderWindow) {
        renderWindow->draw(rect);
    }

    // Draws the Walls of the Tile
    void drawWalls(RenderWindow *renderWindow) {
        for (int x = 0; x < 4; x++) {
            if (wall[x]) {
                renderWindow->draw(Walls[x]);
            }
        }
    }

    // moving the rect for @param x: X and @param y: Y pixels ...
    void move(int x, int y) {
        locX += x;
        locY += y;

        addWalls();

        rect.setPosition(Vector2f(locX, locY));
    }

    // returning if there is a wall at the @param dir: direction
    bool isWall(int dir){
        return wall[dir];
    }

    // returning the x value of the Tile
    virtual int getX(){
        return locX;
    }

    // returning the y value of the Tile
    virtual int getY(){
        return locY;
    }

    // returns any food if there is some on this Tile, but max 10
    int getFood() {
        if (food >= 10) {
            food -= 10;
            return 10;
        } else {
            int tmp = food;
            food = 0;
            return tmp;
        }
    }

// returns all the food currently on the tile
    virtual int isFood() {
        return food;
    }

    // returns true or false respectively to
    // the mouse inside the tile
    bool isInside(int x, int y) {
        return locX <= x && locY <= y
                && locX + width >= x
                && locY + height >= y;
    }

    // drawing the wall and the tile itself combined
    void draw (RenderWindow *window) {
        drawTile(window);
        drawWalls(window);
    }

    // returning the Height of the tile (for displaying it)
    virtual int getHeight() {
        return height;
    }

    // returning the Height of the tile (for displaying it)
    virtual int getWidth() {
        return width;
    }

    // setting the Index of the tile
    virtual int getIndex() const {
        return index;
    }

    // getting the index of the tile for 'Info'
    virtual void setIndex(int index) {
        Tile::index = index;
    }

    // setting the wall at @param dir: direction to @param setWall
    virtual void setWall(int dir, bool setWall) {
        if ( dir % 4 == dir && isSurrounding(dir)) {
            wall[dir] = setWall;
        }
    }

    // returns the surrounding Tile at @param dir: direction
    virtual Tile* getSurrounding(int dir){
        return surrounding[dir];
    }

    // returns if there is something in this Direction (a tile)
    virtual bool isSurrounding(int dir){
        return surrounding[dir] != NULL;
    }

    // sets the @param *tile: Tile next to it in @param dir: direction
    void setSurrounding(int dir, Tile *tile){
        surrounding[dir] = tile;
    }

    // for every special tile: something happens here!
    virtual void doTick() {
        // overridden by every tile where something happens
    }
};




class showTile : public Tile {
protected:

    // values needed to be overridden
    int pubX = -1, pubY = -1, pubHeight, pubWidth, pubIndex = -1, pubFood = 0;

    // pointer to the tile to show
    Tile* tileToShow;

public:

    showTile() {
        // ctr
    }

    // operator overloading, needed not to override the wrong values
    void operator=(Tile *tile){
        tileToShow = tile;
        doTick();
    }

    // returning the public height of the tile
    int getHeight() {
        return pubHeight;
    }

    // returning the public width of the tile
    int getWidth() {
        return pubWidth;
    }

    // returning the (public) X val
    int getX() {
        return pubX;
    }

    // returning the (public) Y val
    int getY() {
        return pubY;
    }

    // returning the index
    int getIndex() const {
        return pubIndex;
    }

    // setting the index
    void setIndex(int index) {
        showTile::pubIndex = index;
    }

    // returning a pointer to the tile currently shown
    Tile* getTileToShow() {
        return tileToShow;
    }

    // sets the Wall at @param dir: direction to @param setWall
    void setWall(int dir, bool setWall) {
        if (dir % 4 == dir ) {
            wall[dir] = setWall;
            tileToShow->setWall(dir, setWall);
        }
    }

    // returning (for security) if there is a tile in @param dir
    bool isSurrounding(int dir) {
        if(tileToShow != NULL)
            return tileToShow->isSurrounding(dir);
        return NULL;
    }

    // returns the tile in the @param dir if there is one
    Tile* getSurrounding(int dir) {
        return tileToShow->getSurrounding(dir);
    }

    // returns the food on the tile (whole)
    int isFood(){
        return pubFood;
    }

    // Whatever happens at a tick is sure to get updated
    void doTick(){
        if (tileToShow != NULL) {
            pubX = tileToShow->getX();
            pubY = tileToShow->getY();
            pubHeight = tileToShow->getHeight();
            pubWidth = tileToShow->getWidth();
            pubIndex = tileToShow->getIndex();
            pubFood = tileToShow->isFood();

            wall[0] = tileToShow->isWall(0);
            wall[1] = tileToShow->isWall(1);
            wall[2] = tileToShow->isWall(2);
            wall[3] = tileToShow->isWall(3);
        }
    }
};







/*
 * Maze: including all the Tiles, used to manipulate only specific Tiles
 * @param xSize: how many tiles are gonna be in x direction
 * @param ySize: how many tiles are gonna be in y direction
 * creating a Maze with with xSize x ySize Tiles
 */
class Maze {

protected:

    // initializing the MAP and the two sizes of the maze
    int sizeX = -1, sizeY = -1;
    vector<vector<Tile> > MAP;

public:
    // creating the Maze with @param xSize times @param ySize Tiles
    Maze(int xSize, int ySize) {
        sizeX = xSize;
        sizeY = ySize;
        MAP = vector<vector<Tile> >( (unsigned int) xSize,
                vector<Tile>( (unsigned int) ySize) );
        for (int i = 0; i < xSize; i++) {
            for (int j = 0; j < ySize; j++) {
                Tile tile;
                tile.setSize(i * 30, j * 30, 30, 30);
                tile.setIndex( i * xSize + j);
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
    void drawMaze (RenderWindow *renderWindow) {
        for (int i = 0; i < sizeX; i++) {
            for (int j = 0; j < sizeY; j++) {
                MAP[i][j].draw(renderWindow);
            }
        }
    }

    // moving the whole maze for @param x: X and @param y: Y pixels
    void move(int x, int y) {
        for (int i = 0; i < sizeX; i++) {
            for (int j = 0; j < sizeY; j++) {
                MAP[i][j].move(x, y);
            }
        }
    }

    // returns the tile the mouse is currently in if it is in one
    Tile *getTileClicked(int x, int y) {
        for (int i = 0; i < sizeX; i++) {
            for (int j = 0; j < sizeY; j++) {
                if (MAP[i][j].isInside(x, y))
                    return &MAP[i][j];
            }
        }
        return NULL;
    };

    // Doing a tick for every tile in the map
    void doTick() {
        for (int i = 0; i < sizeX; i++) {
            for (int j = 0; j < sizeY; j++) {
                MAP[i][j].doTick();
            }
        }
    }

    // returns the tile at the @param index
    Tile* getTile(int index) {
        return &MAP[index / sizeX][index % sizeY];
    }

    // returning a tile at a specific location
    Tile* getTile(int i, int j){
        if(i >= 0 && i < sizeX && j >= 0 && j < sizeY)
            return &MAP[i][j];
        return NULL;
    }

    // returning the sizeX of the Maze
    int getSizeX() {
        return sizeX;
    }

    // returning the sizeY of the Maze
    int getSizeY() {
        return sizeY;
    }
};

#endif
