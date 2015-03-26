#ifndef UI_HPP
#define UI_HPP

#include <TGUI/TGUI.hpp>
#include "maze.h"
#include "ticksystem.h"
#include "mazecreator.h"
#include "ant.h"

#ifndef SOURCES
#define SOURCES "/home/bz/ClionProjects/AntWorld/resources/"
#endif

#define THEME_CONFIG_FILE "/home/bz/ClionProjects/AntWorld/resources/Black.conf"


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

    // pointer for the RenderWindow to display the tile on it
    sf::RenderWindow *window;

    Craver craver;
    perfectCreator perf;
    RandomCreator randomCreator;

public:


    // setting the window needed later
    GraphicsControl(sf::RenderWindow *renderWindow){
        window = renderWindow;
        tileToShowPtr = &tileToShowTile;

        tileToShowTile.setSize(30, 50, 35, 35);
    }


    // adding the gui to the window
    void addGui (tgui::Gui *gui) {

        // button for closing the window (for test purposes)
        tgui::Button::Ptr button( (*gui) );
        button->load(THEME_CONFIG_FILE);
        button->setPosition(20, 440 + 20);
        button->setText("Close");
        button->setCallbackId(10);
        button->bindCallback(tgui::Button::LeftMouseClicked);
        button->setSize(60, 20);

        // Label to show information about the selected tile
        tgui::Label::Ptr label( (*gui ) );
        label->load(THEME_CONFIG_FILE);
        label->setText("Info: \n\n Food: \n\n Scent1: \n\n Scent2: "
            "\n\n Production: \n\n");
        label->setPosition(20, 95 + 20);
        label->setTextColor(sf::Color(200, 200, 200));
        label->setTextSize(12);

        InfoLabel = label;

        // button to change the state of the wall in upper direction
        tgui::Button::Ptr buttonChangeWallUp( (*gui) );
        buttonChangeWallUp->load(THEME_CONFIG_FILE);
        buttonChangeWallUp->setPosition(15, 250 + 20);
        buttonChangeWallUp->setText("ChangeWallUp");
        buttonChangeWallUp->setCallbackId(0);
        buttonChangeWallUp->bindCallback(tgui::Button::LeftMouseClicked);
        buttonChangeWallUp->setSize(90, 20);


        // button to change the state of the wall right to the tile
        tgui::Button::Ptr buttonChangeWallRight( (*gui) );
        buttonChangeWallRight->load(THEME_CONFIG_FILE);
        buttonChangeWallRight->setPosition(15, 280 + 20);
        buttonChangeWallRight->setText("ChangeWallRight");
        buttonChangeWallRight->setCallbackId(1);
        buttonChangeWallRight->bindCallback(tgui::Button::LeftMouseClicked);
        buttonChangeWallRight->setSize(90, 20);


        // button to change the state of the wall lower of the tile
        tgui::Button::Ptr buttonChangeWallDown( (*gui) );
        buttonChangeWallDown->load(THEME_CONFIG_FILE);
        buttonChangeWallDown->setPosition(15, 310 + 20);
        buttonChangeWallDown->setText("ChangeWallDown");
        buttonChangeWallDown->setCallbackId(2);
        buttonChangeWallDown->bindCallback(tgui::Button::LeftMouseClicked);
        buttonChangeWallDown->setSize(90, 20);


        // button to change the state of the wall left of the tile
        tgui::Button::Ptr buttonChangeWallLeft( (*gui) );
        buttonChangeWallLeft->load(THEME_CONFIG_FILE);
        buttonChangeWallLeft->setPosition(15, 340 + 20);
        buttonChangeWallLeft->setText("ChangeWallLeft");
        buttonChangeWallLeft->setCallbackId(3);
        buttonChangeWallLeft->bindCallback(tgui::Button::LeftMouseClicked);
        buttonChangeWallLeft->setSize(90, 20);


        // button to change the state of the ticks -
        // stopped, paused, or started (running)
        tgui::Button::Ptr StartTicksButton( (*gui) );
        StartTicksButton->load(THEME_CONFIG_FILE);
        StartTicksButton->setPosition(500, 30 + 20);
        StartTicksButton->setText("Start");
        StartTicksButton->setCallbackId(4);
        StartTicksButton->bindCallback(tgui::Button::LeftMouseClicked);
        StartTicksButton->setSize(90, 20);

        ticksControl = StartTicksButton;


        // checkbox if it should be allowed to 'Jump'
        tgui::Checkbox::Ptr checkbox(*gui);
        checkbox->load(THEME_CONFIG_FILE);
        checkbox->setPosition(15, 220 + 20);
        checkbox->setText("Moving");
        checkbox->setSize(20, 20);
        checkbox->check();

        advancedMode = checkbox;


        // testConnectedButton, for initiating the A* search
        tgui::Button::Ptr TestConnectedButton( (*gui) );
        TestConnectedButton->load(THEME_CONFIG_FILE);
        TestConnectedButton->setPosition(15, 400 + 20);
        TestConnectedButton->setText("TestConnected");
        TestConnectedButton->setCallbackId(5);
        TestConnectedButton->bindCallback(tgui::Button::LeftMouseClicked);
        TestConnectedButton->setSize(90, 20);




        // creating the menu
        tgui::MenuBar::Ptr menu(*gui);
        menu->load(THEME_CONFIG_FILE);
        menu->setSize(window->getSize().x, 20);

        menu->addMenu("Maze");
        menu->addMenuItem("Maze", "Reset");
        menu->addMenuItem("Maze", "Create Random");
        menu->addMenuItem("Maze", "Create Perfect");

        menu->addMenu("File");
        menu->addMenuItem("File", "Load");
        menu->addMenuItem("File", "Save");
        menu->addMenuItem("File", "Exit");
        menu->bindCallback(tgui::MenuBar::MenuItemClicked);
        menu->setCallbackId(11);


    }

    void handleCallback(tgui::Callback callback) {
        if (callback.id == 11) {
            if (callback.text == "Reset")
                ResetMaze();
            if (callback.text == "Create Random")
                createRandom();
            if (callback.text == "Create Perfect")
                createPerfect();
        }
    }


    // changing the displayed info to another @param tile1: tile
    void changeTextInfoLabel(Tile *tile) {
        tileToShowTile = tile;

        if (connect) {
            craver.setAim(tileToShowPtr->getTileToShow());
            craver.colorPath(sf::Color(sf::Color::Cyan) );
            craver.searchAStar();

            connect = false;
        }
    }



    // updating the InfoLabel and the separately displayed tile
    void updateInfo () {
        tileToShowPtr->doTick();
        InfoLabel->setText("Info: \n "
                "\nIndex: " + std::to_string (tileToShowPtr->getIndex() + 1) +
                "\nX: " + std::to_string (tileToShowPtr->getX() ) +
                "\nY: " + std::to_string (tileToShowPtr->getY() ) +
                "\n\nFood: \n " + std::to_string (tileToShowPtr->isFood() ) );
        tileToShowPtr->draw(window);
    }


    // testing if two tiles are connected, showing it in the GUI if they are
    void testConnectedButtonClicked() {
        connect = true;
        craver.setStart(tileToShowPtr->getTileToShow() );
    }


    // letting the perfectCreator run once
    void createPerfect() {
        perf.start();
    }


    // changing the shown text on the button
    void TicksControlChangeState() {
        if (ticksControl->getText() == "Start" || ticksControl->getText() == "Resume")
            ticksControl->setText("Pause");
        else
            ticksControl->setText("Resume");
    }


    // changes the state of the wall in @param dir
    void changeWalls(int dir, bool move = false) {
        if (dir % 4 == dir) {
            if (tileToShowPtr->isSurrounding(dir)) {
                tileToShowPtr->setWall(dir, !tileToShowPtr->isWall(dir));
                tileToShowPtr->getSurrounding(dir)->setWall( (dir + 2) % 4,
                        !tileToShowPtr->getSurrounding(dir)->isWall( (dir + 2) % 4) );
                if (move)
                    changeTextInfoLabel(tileToShowPtr->getSurrounding(dir) );
            }
        }
    }


    // returns if the Checkbox is checked or not
    bool isAdvancedMode() {
        return advancedMode->isChecked();
    }


    // setting the maze to the craver and the creator
    void setMaze(Maze *maze) {
        craver.setMaze(maze);
        perf.setMaze(maze);
        randomCreator.setMaze(maze);
    }


    // doing a tick - TODO: NOT WORKING YET
    void doTick () {


        if (tick % 10 == 0)
            randomCreator.complete();


        std::cout << "Tick: " << std::to_string(tick) << std::endl;
        tick++;
    }


    // resetting the Maze
    void ResetMaze() {
        perf.ResetMaze();
    }

    void createRandom() {
        randomCreator.reset();
        randomCreator.complete();
    }


};





#endif