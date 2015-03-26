//
// Created by bz on 26.03.15.
//

#ifndef GRAPHICSCONTROL_H
#define GRAPHICSCONTROL_H



#ifndef SOURCES
#define SOURCES "/home/bz/ClionProjects/AntWorld/resources/"
#endif

#define THEME_CONFIG_FILE "/home/bz/ClionProjects/AntWorld/resources/Black.conf"



#include <TGUI/Label.hpp>
#include <TGUI/Button.hpp>
#include <TGUI/Checkbox.hpp>
#include "maze.h"
#include "mazecreator.h"

class GraphicsControl {
protected:
    // pointer to the InfoLabel, the tickControl Button and
    // the advancedMode checkbox for accessing it later
    tgui::Label::Ptr InfoLabel;
    tgui::Button::Ptr ticksControl;
    tgui::Checkbox::Ptr advancedMode;

    int tick = 0;
    bool connect = false;

    // pointer to the showTile and showTile
    showTile *tileToShowPtr;
    showTile tileToShowTile;

    sf::RenderWindow *window;

    Craver craver;
    perfectCreator perf;
    RandomCreator randomCreator;

public:
    GraphicsControl(sf::RenderWindow *renderWindow);
    void addGui(tgui::Gui *gui);
    void setMaze(Maze *maze);
    void changeTextInfoLabel(Tile *tile);
    void updateInfo();
    void testConnectedButtonClicked();
    void createPerfect();
    void createRandom();
    void ResetMaze();
    bool isAdvancedMode();
    void changeWalls(int dir, bool move = false);
    void TicksControlChangeState();
    void doTick();
};











#endif //_ANTWORLD_GRAPHICSCONTROL_H_
