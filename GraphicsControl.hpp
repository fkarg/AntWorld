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
        button->setText("Button1");
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

    }

    // changing the displayed info to another @param tile1: tile
    void changeTextInfoLabel(Tile *tile1) {
        tile = tile1;
        updateInfo();
    }

    // updating the InfoLabel and the seperately displayed tile
    void updateInfo () {
        InfoLabel->setText("Info: \n "
                "\nX: " + std::to_string (tile->getX() ) +
                "\nY: " + std::to_string (tile->getY() ) +
                "\n\nFood: \n " +
                std::to_string (tile->isFood() ) );
        tile->draw(window);
    }


};





#endif