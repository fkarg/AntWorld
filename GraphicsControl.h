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

    showAnt *antToShowPtr;
    showAnt antToShowAnt;

    Ant selectedAnt;

    Maze* maze;

    sf::RenderWindow* window;

    Craver craver;
    perfectCreator perf;
    RandomCreator randomCreator;

public:
    GraphicsControl(sf::RenderWindow *renderWindow);
    void addGui(tgui::Gui *gui);
    void setMaze(Maze *maze);
    void changeTextInfoLabel(Tile *tile);
    void AntMove(int dir);
    void updateInfo();
    void testConnectedButtonClicked();
    void handleCallback(tgui::Callback callback);
    void createPerfect();
    void createRandom();
    void ResetMaze();
    bool isAdvancedMode();
    void changeWalls(int dir, bool move = false);
    void TicksControlChangeState();
    void drawAnts();
    void doTick();
};











#endif
