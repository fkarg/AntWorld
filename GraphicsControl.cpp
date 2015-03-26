//
// Created by bz on 26.03.15.
//

#include "GraphicsControl.h"


//





GraphicsControl::GraphicsControl(sf::RenderWindow *renderWindow) {
    window = renderWindow;
    tileToShowPtr = &tileToShowTile;

    tileToShowTile.setSize(30, 50, 35, 35);
}


void GraphicsControl::addGui(tgui::Gui *gui) {

    // button for closing the Window (for test purposes)
    tgui::Button::Ptr button( (*gui) );
    button->load(THEME_CONFIG_FILE);
    button->setPosition(20, 460);
    button->setSize(60, 20);
    button->setText("Close");
    button->bindCallback(tgui::Button::LeftMouseClicked);
    button->setCallbackId(10);


    // label to show information about the selected Tile
    tgui::Label::Ptr infoLabel( (*gui) );
    infoLabel->load(THEME_CONFIG_FILE);
    infoLabel->setPosition(20, 115);
    infoLabel->setTextSize(12);
    infoLabel->setTextColor(sf::Color(200, 200, 20) );
    infoLabel->setText("Info: ...");

    InfoLabel = infoLabel;


    // button to change the state of the wall in upper direction to tho tile selected
    tgui::Button::Ptr buttonChangeWallUp( (*gui) );
    buttonChangeWallUp->load(THEME_CONFIG_FILE);
    buttonChangeWallUp->setPosition(15, 270);
    buttonChangeWallUp->setSize(90, 20);
    buttonChangeWallUp->bindCallback(tgui::Button::LeftMouseClicked);
    buttonChangeWallUp->setCallbackId(0);
    buttonChangeWallUp->setText("ChangeWallsUp");


    // button to change the state of the wall right to the tile selected
    tgui::Button::Ptr buttonChangeWallRight = buttonChangeWallUp;
    buttonChangeWallRight->setPosition(15, 300);

}






