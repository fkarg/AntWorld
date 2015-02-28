#ifndef UI_HPP
#define UI_HPP
#define THEME_CONFIG_FILE "resources/Black.conf"

#include <TGUI/TGUI.hpp>
#include "maze.hpp"




class GraphicsControl {
private:
    tgui::Label::Ptr InfoLabel;
    Tile *tile;
    sf::RenderWindow *window;
protected:
    // ...
public:
    // setting the window needed later
    GraphicsControl(sf::RenderWindow *renderWindow){
        window = renderWindow;
    }

    // adding the gui to the window
    void addGui (tgui::Gui *gui) {
        tgui::Button::Ptr button( (*gui) );
        button->load(THEME_CONFIG_FILE);
        button->setPosition(20, 25);
        button->setText("Close");
        button->setCallbackId(1);
        button->bindCallback(tgui::Button::LeftMouseClicked);
        button->setSize(60, 20);

        tgui::Label::Ptr label( (*gui ) );
        label->load(THEME_CONFIG_FILE);
        label->setText("Info: \n\n Food: \n\n Scent1: \n\n Scent2: "
            "\n\n Production: \n\n");
        label->setPosition(20, 120);
        label->setTextColor(sf::Color(200, 200, 200));
        label->setTextSize(12);

        InfoLabel = label;

        // TODO: buttons to change the walls of the currently selected Tile


        //////////////////////////////////////////////////////////
        /////           experimental:                       //////
        //////////////////////////////////////////////////////////


        tgui::Button::Ptr buttonChangeWallUp( (*gui) );
        buttonChangeWallUp->load(THEME_CONFIG_FILE);
        buttonChangeWallUp->setPosition(15, 250);
        buttonChangeWallUp->setText("ChangeWallUp");
        buttonChangeWallUp->setCallbackId(2);
        buttonChangeWallUp->bindCallback(tgui::Button::LeftMouseClicked);
        buttonChangeWallUp->setSize(90, 20);


        tgui::Button::Ptr buttonChangeWallDown( (*gui) );
        buttonChangeWallDown->load(THEME_CONFIG_FILE);
        buttonChangeWallDown->setPosition(15, 280);
        buttonChangeWallDown->setText("ChangeWallDown");
        buttonChangeWallDown->setCallbackId(2);
        buttonChangeWallDown->bindCallback(tgui::Button::LeftMouseClicked);
        buttonChangeWallDown->setSize(90, 20);


        tgui::Button::Ptr buttonChangeWallRight( (*gui) );
        buttonChangeWallRight->load(THEME_CONFIG_FILE);
        buttonChangeWallRight->setPosition(15, 310);
        buttonChangeWallRight->setText("ChangeWallRight");
        buttonChangeWallRight->setCallbackId(2);
        buttonChangeWallRight->bindCallback(tgui::Button::LeftMouseClicked);
        buttonChangeWallRight->setSize(90, 20);


        tgui::Button::Ptr buttonChangeWallLeft( (*gui) );
        buttonChangeWallLeft->load(THEME_CONFIG_FILE);
        buttonChangeWallLeft->setPosition(15, 340);
        buttonChangeWallLeft->setText("ChangeWallLeft");
        buttonChangeWallLeft->setCallbackId(2);
        buttonChangeWallLeft->bindCallback(tgui::Button::LeftMouseClicked);
        buttonChangeWallLeft->setSize(90, 20);

    }

    // changing the displayed info to another @param tile1: tile
    void changeTextInfoLabel(Tile *tile1) {
        tile = tile1;
        updateInfo();
    }

    // updating the InfoLabel and the seperately displayed tile
    void updateInfo () {
        InfoLabel->setText("Info: \n "
                "\nIndex: " + std::to_string (tile->getIndex() ) +
                "\nX: " + std::to_string (tile->getX() ) +
                "\nY: " + std::to_string (tile->getY() ) +
                "\n\nFood: \n " +
                std::to_string (tile->isFood() ) );
        tile->draw(window);
    }


};





#endif