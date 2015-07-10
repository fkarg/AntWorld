#ifndef TILE_H
#define TILE_H


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "ticksystem.h"



// possible states for every tile
enum STATE {
    // 0     1    2
    NORMAL, ANT, RES,
    //  3      4      5
    RES_ANT, BASE, BASE_ANT,
    //  6           7
    BASE_RES, BASE_RES_ANT
};



class Ant;
class antBase;
class producing;
class showTile;



class Tile : public tickInterface {
protected:
    int locX, locY, height, width, index = -1;
    int Scents[3] = {0, 0, 0}, scentID[3] = {0, 0, 0}, scentCount = 0;

    STATE current = NORMAL; // the state the tile currently has

    // bool wall[4] = { false, false, false, false };
    bool wall[4] = { true, true, true, true };
//    the directions: up, right, down, left
//                     0 ,   1 ,   2 ,   3

    Tile* surrounding[4] = {}; // to direct to tiles next to it

    // RectangleShapes to draw the tile and the walls later on
    sf::RectangleShape rect;
    sf::RectangleShape Walls[4];

    antBase* base = NULL;       // the AntBase, for later referring to it
    producing* res = NULL;

    std::vector<Ant*> ownAnts;      // the vector of all Ants currently on this Tile


    void addWalls();                // adding or actualizing the Walls position
    void addState(STATE state);     // adding the @param state if needed
    bool removeState(STATE state);  // removing the @param state if necessary

public:
    Tile(){};
    // setting the coordinates and the size of the tile
    virtual void setSize(int x, int y, int width, int height);
    virtual int getX();         // returning x
    virtual int getY();         // returning y
    void move(int x, int y);    // moving it @param x and @param y pixels
    bool isInside(int x, int y);// returning if the mouse is inside the tile
    virtual int getHeight();    // getting the height of the Tile
    virtual int getWidth();     // getting the width of the Tile
    virtual void setIndex(int index); // setting the @param index
    virtual int getIndex() const;     // the set index
    void setColor(sf::Color color);   // setting the color of the Tile
    sf::Color getTileColor();         // returns the current color of the tile
    void draw(sf::RenderWindow* window); // drawing the Tile completely (obsolete)
    virtual void drawTile(sf::RenderWindow* window); // drawing only the body of the Tile
    void drawWalls(sf::RenderWindow* window);    // drawing only the Walls of the Tile
    void doTick();                               // doing a Tick
    virtual void setWall(int dir, bool setWall); // setting the wall in @param dir to @param setWall
    bool isWall(int dir);       // returning if there is a wall in this @param dir
    void setSurrounding(int dir, Tile* tile); // setting in @param dir the @param tile
    virtual Tile* getSurrounding(int dir);    // returning the tile in @param dir
    virtual bool isSurrounding(int dir); // returning if there even is sth in @param dir
    virtual int isFood();          // returning all the food on the Tile
    int getFood(Ant* ant = NULL);  // returning 0 up to 10 max food and decreasing it on the Tile
    virtual std::string getTileInfo();   // returns the TileInfoLabel of the tile

    antBase* getBase() { return base; }  // returns the antBase if one is set
    void setBase(antBase* base);         // setting the antBase
    virtual void removeBase();           // removing the base, needed when destroyed or sth

    void setRes(producing* produ);        // setting the @param res on this tile
    producing* getRes() { return res; } // @return the producing part of the tile
    void removeRes();                   // removing the resource-producing part from the tile

    void addAnt(Ant* ant);              // adding the @param ant to tile
    bool removeAnt(unsigned int AntID); // @return if the AntID's ant was on the tile before, is not from now on anyways
    Ant* getAnt();                      // @returns the ant that got first on this tile
    int getAntCount();                  // @returns how many ants there are exactly on this tile

    int getScentCount() { return scentCount; }
    int getScent(int which = 0);    // @returns the scent on place @param which
    int getOwnScent(Ant* who);      // @returns the own scent of @param who or -1
    int getTeamScent(Ant* who);     // @returns the strongest team-scent or -1
    int getScentID(int which);      // @returns the ScentID on place @param which
    void addScent(Ant* from);       // simply adds a scent to the tile, @param from's AntID is saved

    bool isBASE();      // returns if the Tile has the special case 'BASE'
    bool hasAnt();      // returns if the Tile has the special case 'Ant'
    bool isRES();       // returns if the Tile has the special case 'RES'
};




class producing : public tickInterface {
private:
    float production = 0.0, produced = 0.0;
    bool isProducing = true; // if there's production currently

    sf::Texture texture;   // the texture of the tile
    sf::Sprite sprite;     // the sprite to show the texture

    Tile* tile = NULL;

public:
    producing(){}

    void setPosition(Tile* loc);      // setting the position of the RES to @param loc
    void setPosition(showTile* loc);  // setting the position to the showTile

    void reloadImage();               // reloading the at some point maybe corrupted image

    void setProductionRate(float prod);   // setting the production of the tile to @param prod
    void setProducing(bool nowprod);  // setting the production to @param nowprod
    bool getProducingState();         // @return if currently is produced or not
    float getProductionRate();        // @return the rate of the production, if there's production to begin with
    float getProduced();              // @return the produced food on this tile (possibly not everything produced)
    int getFood();                    // an ant visited and took up to ten 'food'

    Tile* getLoc() { return tile; }   // @returns the tile this res is located on

    void draw(sf::RenderWindow* window); // drawing the image on the @param window

    void doTick();                    // adds the productionRate to the currently produced

    ~producing();                     // destructor - necessary?

};



class showTile : public Tile {

protected:
    int pubX = -1, pubY = -1, pubIndex = -1;
    unsigned int pubFood = 0;
    Tile* tileToShow = NULL;    // the tile that is being 'copied'

public:
    showTile(){};
    void operator=(Tile *tile); // for getting the right values
    int getHeight();    // returning the height
    int getWidth();     // returning the width
    int getX();         // returning x
    int getOwnX();      // returning the own X value
    int getY();         // returning y
    int getOwnY();      // returning the own Y value
    void setIndex(int index); // setting the @param index
    int getIndex();     // returning the index
    int isFood();       // returning how much food there is on the Tile
    void setWall(int dir, bool setWall); // setting in @param dir the @param setWall
    void doTick();      // whatever happens at a tick TODO: updating the info seperately
    bool isSurrounding(int dir); // returns if there virtually is a tile next to it in @param dir
    Tile* getSurrounding(int dir); // getting the virtually surrounding tile
    Tile* getTileToShow(); // returns the tile it 'copies' or at least shows
    std::string getTileInfo(); // returns the info of the currently selected tile (when)

    void removeBase();      // removes the Base from the showTile
};




class Tile_lite {
private:
	int index = -1, AntsOn = 0;
	STATE current = NORMAL;
	bool wasFoodOnIt = false, wasScentOnIt = false;
	bool wall[4] = { true, true, true, true };
	Tile_lite* surrounding[4] = { NULL, NULL, NULL, NULL };
	sf::Color TileColor = sf::Color::BLUE;
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
	bool hasAnt(); // @retuns if there's an ant on this tile TODO: relevant?
	bool isRes(); // @returns if there's a res on this tile
};








#endif


