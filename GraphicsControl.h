//
// Created by bz on 26.03.15.
//

#ifndef GRAPHICSCONTROL_H
#define GRAPHICSCONTROL_H



#ifndef SOURCES
#define SOURCES "/usr/resources_coding/"
#endif

#define THEME_CONFIG_FILE "/usr/resources_coding/Black.conf"                                    



#include <TGUI/TGUI.hpp>
#include "maze.h"
#include "mazecreator.h"
#include "ticksystem.h"
#include "ant.h"


class GraphicsControl : public tickInterface {
protected:
    // pointer to the TileInfoLabel, the tickControl Button and
    // the advancedMode checkbox for accessing it later
    tgui::Label::Ptr TileInfoLabel, AntInfoLabel;
    tgui::Button::Ptr ticksControl, setHomeButton;
    tgui::Checkbox::Ptr advancedMode;
    tgui::Slider::Ptr slider;

    int tick = 0;
    bool connect = false, drawBase = false;

    // pointer to the showTile and showTile
    showTile *tileToShowPtr;
    showTile tileToShowTile;

    showAnt *antToShowPtr;
    showAnt antToShowAnt;

    Ant selectedAnt;

    Maze* maze;
    antBase base;

    sf::RenderWindow* window;

    Craver craver;
    perfectCreator perf;
    RandomCreator randomCreator;

public:
    GraphicsControl(sf::RenderWindow *window); // setting the pointers
    void addGui(tgui::Gui *gui);        // adding the gui and adding the @param tgui
    void setMaze(Maze *maze);           // setting the @param maze in which everything happens
    void changeTextInfoLabel(Tile *tile); // changing the TileInfoLabel to @param tile
    void AntMove(int dir);              // moving the ant in @param dir
    void updateInfo();                  // updating the infoLabels
    void testConnectedButtonClicked();  // if the testConnectedButton is clicked
    void handleCallback(tgui::Callback callback); // handles the callback of the tgui
    void createPerfect();               // creates a perfect maze
    void createRandom();                // creates a random maze
    void ResetMaze();                   // resets the maze completely
    void sliderValueChanged();          // gets called whenever the value of the slider changes
    bool isAdvancedMode();              // returns if the advancedMode checkbox is checked
    void changeWalls(int dir, bool move = false); // changes the walls in @param dir and @param moves
    void TicksControlChangeState();     // changes the state of the ticksControl
    void drawAnts();                    // draws the Ants (showAnt & selectedAnt)
    Tile *getTileSelected();            // returns the currently selected tile
    void doTick();                      // for the implementation
};











#endif
