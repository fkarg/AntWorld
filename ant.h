#ifndef ANT_H
#define ANT_H

#include <SFML/Graphics/Texture.hpp>
#include "ticksystem.h"
#include "tile.h"

#include <iostream>
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#ifndef SOURCES
#define SOURCES "/usr/resources_coding/"
#endif


class Maze;


static unsigned int MAXANTID; // keeps track of the AntID's
static unsigned int MAXTEAMNUM; // keeps track of the number of teams


class Ant : public tickInterface {

protected:
    int locX = -1, locY = -1, dir = 0, height = 26, width = 26;

    unsigned int ownFood = 0, AntID, TeamNum = 0;

    sf::Texture texture;
    sf::Sprite sprite;

    Tile* current = NULL;   // FIXME: when trying to compare Indexes ...

    antBase* home = NULL;

public:
    Ant();
    void reloadImage();     // reloads the maybe corrupted image of the ant
    void setHome(antBase* home); // setting the Home of the Ant
    unsigned int getTeamNum() { return TeamNum; }
    int getX();             // returns the x-val of the ant
    int getY();             // returns the y-val of the ant
    int getDir();           // returns the current dir of the ant
    unsigned int getFood(); // returns the current food of the ant
    Tile* getCurrent();     // returns the tile the ant is currently on
    void setCurrent(Tile *current); // setting the tile the ant is currently on
    void setAntID(unsigned int newID); // setting the unique antID
    unsigned int getID();   // getting the AntID
    void setPosition(Tile *tileToGoOn) { setCurrent(tileToGoOn); } // see getCurrent
    virtual void move(int dir); // moving the ant if it is possible in @param dir
    virtual void draw(sf::RenderWindow *window); // draws the ant
    void senseFoodOnCurrentTile(); // TODO: sensing etc
    void doTick();          // doing a tick
    bool isInside(int x, int y); // returns if the ant got clicked

    static void initAntCount() { MAXANTID = 0; }
};






class showAnt : public Ant {

protected:
    int pubX = -1, pubY = -1;
    bool isVisible = false;
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
};






class antBase : public tickInterface {

private:
    sf::Texture texture;
    sf::Sprite sprite;
    Ant ownAnts[20] = {};
    Tile *baseTile = NULL;
    int locX, locY, AntCount = 0;
    bool isVisible = true;
    Maze *maze;
    unsigned int TeamNum;

public:
    antBase() { reloadBase(); TeamNum = MAXTEAMNUM++; }     // loads the baseImage
    void reloadBase();              // reloads the baseImage
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
    int getAntCount() { return AntCount; }  // returns the number of ants from this base
    Ant *getAnt(unsigned int AntID); // returns the ant with the @param AntID
    Tile *getTile() { return baseTile; } //returns the baseTile
    unsigned int getTeamNum() { return TeamNum; }

    static void initTEAMS() { MAXTEAMNUM = 0; } // initializing the number of teams
};










#endif

