#ifndef MAZE_LITE_H
#define MAZE_LITE_H



class Tile_lite {
private:
    int index = -1, AntsOn = 0;
    STATE current = NORMAL;
    bool wasFoodOnIt = false, wasScentOnIt = false;
    bool wall[4] = { true, true, true, true };
    Tile_lite* surrounding[4] = { NULL, NULL, NULL, NULL };
    sf::Color TileColor = sf::Color::Blue;
public:
    Tile_lite(){};
    void setIndex(int index); // setting the Index of the current tile to @param index
    int getIndex(); // returns the index of the cue
    void setColor(sf::Color color); // setting the @param color of the tile
    sf::Color getColor(); // @returns the color of the @param tile
    void setWall(int dir, bool isWall); // sets in @param dir the wall to @param setWall
    bool isWall(int dir); // @returns if there's a wall in @param dir
    void setSurrounding(int dir, Tile_lite* tile); // setting in @paramr dir the @param tile surrounding
    Tile_lite* getSurrounding(int dir); // @returns in @param dir the surrounding
    bool isSurrounding(int dir); // @returns if there's a tile in @param dir
    void setFood(bool isThere); // sets if there was food to @param isThere
    bool wasFood(); // @returns if there was food on this tile
    void setScent(bool isThere); // sets if there was scent there to @param isThere
    bool wasScent(); // @returns if there was scent on this tile

    bool isBase(); // @returns if there's a base on this tile
    bool hasAnt(); // @returns if there's an ant on this tile TODO: relevant?
    bool isRes(); // @returns if there's a res on this tile
};





class Maze_lite : public tickInterface {
private:
    int sizeX = -1, sizeY = -1;
    std::vector<std::vector<Tile_lite> > MAP;
    int prodNums = 0, baseNums = 0;
    void setNeighbourTiles();

public:
    Maze_lite(int xSize, int ySize); // creates a maze with @param xSize * @param ySize tiles
    int getSizeX(); // @returns the SizeX of the maze
    int getSizeY(); // @returns the SizeY of the maze
    int INDEX_MAX(); // @returns the max_index of the maze (sizeX * sizeY)
    Tile_lite& getAtIndex(int index); // @returns the &tile at @param index

};





#endif
