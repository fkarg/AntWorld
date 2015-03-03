#ifndef UI_HPP
#define UI_HPP
#define THEME_CONFIG_FILE "resources/Black.conf"

#include <TGUI/TGUI.hpp>
#include "maze.hpp"


class GraphicsControl {
protected:
    // pointer to the InfoLabel for accessing it later
    tgui::Label::Ptr InfoLabel;

    tgui::Button::Ptr ticksControl;

    int tick = 0;

    // pointer to the showTile and showTile
    showTile *tileToShowPtr;
    showTile tileToShowTile;

    // pointer for the RenderWindow to display the tile on it
    sf::RenderWindow *window;

public:
    // setting the window needed later
    GraphicsControl(sf::RenderWindow *renderWindow){
        window = renderWindow;
        tileToShowPtr = &tileToShowTile;

        tileToShowTile.setSize(30, 30, 35, 35);
    }

    // adding the gui to the window
    void addGui (tgui::Gui *gui) {

        // button for closing the window (for test purposes)
        tgui::Button::Ptr button( (*gui) );
        button->load(THEME_CONFIG_FILE);
        button->setPosition(20, 400);
        button->setText("Close");
        button->setCallbackId(10);
        button->bindCallback(tgui::Button::LeftMouseClicked);
        button->setSize(60, 20);

        // Label to show information about the selectedt tile
        tgui::Label::Ptr label( (*gui ) );
        label->load(THEME_CONFIG_FILE);
        label->setText("Info: \n\n Food: \n\n Scent1: \n\n Scent2: "
            "\n\n Production: \n\n");
        label->setPosition(20, 95);
        label->setTextColor(sf::Color(200, 200, 200));
        label->setTextSize(12);

        InfoLabel = label;

        // button to change the state of the wall in upper direction
        tgui::Button::Ptr buttonChangeWallUp( (*gui) );
        buttonChangeWallUp->load(THEME_CONFIG_FILE);
        buttonChangeWallUp->setPosition(15, 250);
        buttonChangeWallUp->setText("ChangeWallUp");
        buttonChangeWallUp->setCallbackId(0);
        buttonChangeWallUp->bindCallback(tgui::Button::LeftMouseClicked);
        buttonChangeWallUp->setSize(90, 20);


        // button to change the state of the wall right to the tile
        tgui::Button::Ptr buttonChangeWallRight( (*gui) );
        buttonChangeWallRight->load(THEME_CONFIG_FILE);
        buttonChangeWallRight->setPosition(15, 280);
        buttonChangeWallRight->setText("ChangeWallRight");
        buttonChangeWallRight->setCallbackId(1);
        buttonChangeWallRight->bindCallback(tgui::Button::LeftMouseClicked);
        buttonChangeWallRight->setSize(90, 20);


        // button to change the state of the wall lower of the tile
        tgui::Button::Ptr buttonChangeWallDown( (*gui) );
        buttonChangeWallDown->load(THEME_CONFIG_FILE);
        buttonChangeWallDown->setPosition(15, 310);
        buttonChangeWallDown->setText("ChangeWallDown");
        buttonChangeWallDown->setCallbackId(2);
        buttonChangeWallDown->bindCallback(tgui::Button::LeftMouseClicked);
        buttonChangeWallDown->setSize(90, 20);


        // button to change the state of the wall left of the tile
        tgui::Button::Ptr buttonChangeWallLeft( (*gui) );
        buttonChangeWallLeft->load(THEME_CONFIG_FILE);
        buttonChangeWallLeft->setPosition(15, 340);
        buttonChangeWallLeft->setText("ChangeWallLeft");
        buttonChangeWallLeft->setCallbackId(3);
        buttonChangeWallLeft->bindCallback(tgui::Button::LeftMouseClicked);
        buttonChangeWallLeft->setSize(90, 20);


        tgui::Button::Ptr StartTicksButton( (*gui) );
        StartTicksButton->load(THEME_CONFIG_FILE);
        StartTicksButton->setPosition(90, 30);
        StartTicksButton->setText("Start");
        StartTicksButton->setCallbackId(4);
        StartTicksButton->bindCallback(tgui::Button::LeftMouseClicked);
        StartTicksButton->setSize(90, 20);

        ticksControl = StartTicksButton;

    }

    // changing the displayed info to another @param tile1: tile
    void changeTextInfoLabel(Tile *tile1) {
        tileToShowTile =  tile1;
    }

    // updating the InfoLabel and the seperately displayed tile
    void updateInfo () {
        InfoLabel->setText("Info: \n "
                "\nIndex: " + std::to_string (tileToShowPtr->getIndex() ) +
                "\nX: " + std::to_string (tileToShowPtr->getX() ) +
                "\nY: " + std::to_string (tileToShowPtr->getY() ) +
                "\n\nFood: \n " +
                std::to_string (tileToShowPtr->isFood() ) );
        tileToShowPtr->draw(window);
    }

    // changes the state of the wall in @param dir
    void changeWalls(int dir) {
        if (dir % 4 == dir) {
            if (tileToShowPtr->isSurrounding(dir)) {
                tileToShowPtr->setWall(dir, !tileToShowPtr->isWall(dir));
                tileToShowPtr->getSurrounding(dir)->setWall( (dir + 2) % 4,
                        !tileToShowPtr->getSurrounding(dir)->isWall( (dir + 2) % 4) );
                // FIXME: tile = tile->getSurrounding(dir);
                // changeInfoTile(tile->getSurrounding(dir) );
            }
        }
    }

    void DoTick () {




        std::cout << "Tick: " << std::to_string(tick) << std::endl;
        tick++;
    }


};





#endif