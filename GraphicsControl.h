//
// Created by bz on 26.03.15.
//

#ifndef GRAPHICSCONTROL_H
#define GRAPHICSCONTROL_H


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

    // pointer to the showtile
    showTile *tileToShowPtr;
    showTile tileToShowTile;

    sf::RenderWindow *window;

    Craver craver;
    perfectCreator perf;


public:
    GraphicsControl(sf::RenderWindow *renderWindow);
    void addGui(tgui::Gui *gui);
    void changeTextInfoLabel(Tile *tile);
    void updateInfo();
    void testConnectedButtonClicked();
    void createPerfect();
    void TicksControlChangeState();
    void changeWalls(int dir, bool move = false);
    bool isAdvancedMode();
    void setMaze(Maze *maze);
    void doTick();
    void ResetMaze();
};











#endif //_ANTWORLD_GRAPHICSCONTROL_H_
