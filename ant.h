#ifndef ANT_H
#define ANT_H

#include <SFML/Graphics/Texture.hpp>
#include "ticksystem.h"
#include "tile.h"
#include "ai.h"
#include "maze_lite.h"

#include <iostream>
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#ifndef SOURCES
#define SOURCES "/usr/resources_coding/"
#endif

#define START_FOOD 200


class Maze;


static unsigned int MAXANTID; // keeps track of the AntID's
static unsigned int MAXTEAMNUM; // keeps track of the number of teams
static const unsigned int MAX_FOOD_ANT_CARRYING = 30;
static ai AI;

class Ant : public tickInterface {

protected:
    int locX = -1, locY = -1, dir = 0, height = 26, width = 26, lastAction = 6;

    unsigned int ownFood = 2, AntID, TeamNum = 0, livingForTicks = 5;

    bool isDead = true;

    sf::Texture texture;
    sf::Sprite sprite;

    Tile* current = NULL;

    antBase* home = NULL;

public:
    Ant();
    void reloadImage();     // reloads the maybe corrupted image of the ant
    void setHome(antBase* home); // setting the Home of the Ant
    unsigned int getTeamNum() { return TeamNum; } // returns the teamNum of the ant
    int getX();             // returns the x-val of the ant
    int getY();             // returns the y-val of the ant
    int getDir();           // returns the current dir of the ant
    unsigned int getFood(); // returns the current food of the ant
    void remFood(unsigned int num); // removes food from the ant that got added elsewhere
    void addFood(unsigned int number); // adds @param number much food to the ant if possible
    void BaseFoodCommunicate(); // requests needed food from the base itself or gives own food to the base
    Tile* getCurrent();     // returns the tile the ant is currently on
    void setCurrent(Tile* current); // setting the tile the ant is currently on
    void setAntID(unsigned int newID); // setting the unique antID
    unsigned int getID();   // getting the AntID
    void setPosition(Tile* tileToGoOn) { setCurrent(tileToGoOn); } // see getCurrent
    virtual void move(int dir); // moving the ant if it is possible in @param dir
    virtual void draw(sf::RenderWindow *window); // draws the ant
    void doTick();          // doing a tick
    bool isInside(int x, int y); // returns if the ant got clicked

    void Dies();            // what happens when the ant is 'dead'
    void live();            // getting the ant to live for the first time
    void relive(Tile* pos); // 'bringing the ant back to live' at @param pos
    bool isInTeam(unsigned int AntID); // @returns if the @param AntID is in the own Team

    unsigned int getTicksLiving();      // the number of Ticks the Ant will be alive for definitely
    virtual void testLiving();          // testing if the Ant is still Alive or is just a ghost
    bool getDead() { return isDead; }   // returns if the ant is dead yet
    int getLastAction() { return lastAction; } // @returns the action the ant did last
    void setLastAction(int what) { lastAction = what; } // setting what the last action actually was
    static void initAntCount() { MAXANTID = 0; } // initiating the AntCount
};






class showAnt : public Ant {

protected:
    int pubX = -1, pubY = -1;
    bool isVisible = false, autoColor = true;
    showTile* showingTile;
    Ant* AntToShow;

public:
    showAnt();
    void operator=(Ant* newAnt);    // overriding the operator= for a normal ant
    void setAnt(Ant* newAnt);       // setting the ant explicitly
    void setDir(int dir);           // setting the dir of the ant
    // setting the position of the showAnt on the showTile
    void setPosition(showTile *showTile1);
    void setVisible(bool visible);  // setting the visibility (the focus) of the ant
    bool getVisible();              // returns if the ant is visible right now or not
    void move(int dir);             // 'moving' the showAnt and the antToShow
    void setPosition(int dir);      // setting the Position relational to the @param dir
    void draw(sf::RenderWindow *window); // drawing the ant if it is visible right now
    Ant* getAntShown();             // returns the ant currently shown, if visible
    void testLiving(){};            // making the showAnt undying
    void doTick();                  // doing the tick
};






class antBase : public tickInterface {

private:
    sf::Texture texture;
    sf::Sprite sprite;
    Ant ownAnts[20] = {};
    bool dead[20] = { false };
    Tile* baseTile = NULL;
    int locX, locY, AntCount = 0, RealAntCount = 0, deadCount = 0;
    bool isVisible = true, autoColor = true;
    sf::Color BaseColor;
    Maze* maze;
    unsigned int TeamNum, food = START_FOOD;

public:
    antBase() { TeamNum = MAXTEAMNUM++; reloadBase(); }     // loads the baseImage
    void reloadBase();              // reloads the baseImage
    sf::Color getColor();           // @returns the color of the base and with it of the team
    void setColor(sf::Color color); // setting the color of the Base (for the showBase) to @param color
    void setMaze(Maze *maze);       // sets the @param maze
    void setPosition(int x, int y, float scale = 0.2); // sets the Position of the Base
    void setPosition(Tile *tile, float scale = 0.2);   // sets the Position of the BaseImage
    // setting the BaseTile unspecific to the Position (...)
    void setBase(Tile *tile) { baseTile = tile; }
    void addAnt();                  // adds a new ant to the AntBase
    void addAnt(Ant ant);           // adds a specific @param ant to the antBase
    void addAnts(int num);          // adding @param num new ants to the antBase
    void drawAnts(sf::RenderWindow *window); // draws the Ants of the antBase
    void drawBase(sf::RenderWindow *window); // draws the antBase itself
    void draw(sf::RenderWindow *window);     // draws tha antBase and the ants
    void doTick();                  // does the tick for all the ants
    void setVisible(bool visible) { isVisible = visible; } // setting if the icon is getting drawn
    bool getVisible() { return isVisible; } // returns if the tile is currently visible
    int getAntCount() { return RealAntCount; }  // returns the number of ants from this base
    Ant* getAntWith(unsigned int AntID); // @returns the ant with the @param AntID
    Ant* getAnt(int Index, bool deadToo = false);         // @returns the ant at @param Index
    Tile* getTile() { return baseTile; } // @returns the baseTile
    unsigned int getTeamNum() { return TeamNum; } // @returns the unique teamNum

    void addFood(unsigned int number);      // adding @param number food to the antBase
    unsigned int getFood(Ant* ant, unsigned int number = 10); // @returns food for the @param ant
    unsigned int isFood();                  // returns if there's food on this tile and how many

    void decRealAntCount(Ant* ant);         // lets the @param ant die
    int getDeadIt();                        // returns an iterator of a dead ant or else -1

    static void initTEAMS() { MAXTEAMNUM = 0; } // initializing the number of teams
};










#endif

