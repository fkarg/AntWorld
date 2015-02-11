#ifndef UI_HPP
#define UI_HPP
#define THEME_CONFIG_FILE TGUI/widgets/Black.conf"

#include "TGUI/include/TGUI/TGUI.hpp"



using namespace std;
using namespace sf;



class GUI {
private:
    RenderWindow window;
    tgui::Gui gui;
    void createGUI(RenderWindow wind){
        window = wind;
        tgui::Gui gui(window);

        tgui::Button::Ptr button(gui);
        button->load(THEME_CONFIG_FILE);
        button->setPosition(40, 25);
        button->setText("BUTTÖÖÖN");
        button->setCallbackId(1);
        button->bindCallback(tgui::Button::LeftMouseClicked);
        button->setSize(300, 40);

        // TODO: create GUI!
    }
    // ...
protected:
    // ...
public:
    // ...
    void create(RenderWindow wind){
        createGUI(wind);
    }

    void handleEvent(Event event){
        gui.handleEvent(event);
    }

    void draw(){
        gui.draw();
    }
};