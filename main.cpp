#include <TGUI/TGUI.hpp>
#include "GraphicsControl.hpp"
#include "maze.hpp"
#include <iostream>

#define THEME_CONFIG_FILE "resources/Black.conf"

int main()
{

    std::cout << "creating window and gui ..." << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "TGUI window");
    tgui::Gui gui(window);

    std::cout << "setting global font ..." << std::endl;

    if (!gui.setGlobalFont("resources/DejaVuSans.ttf"))
        return 1;

    /// tgui::Picture::Ptr picture(gui);
    /// picture->load("resources/Black.png");

    std::cout << "creating Button ..." << std::endl;

    // creating the GraphicsControl
    GraphicsControl control (&window);
    control.addGui(&gui);

    std::cout << "creating maze ... " << std::endl;

    Maze maze(10, 10);

    Tile tile;

    tile.setSize(40, 60, 35, 35);

    control.changeTextInfoLabel(&tile);

    std::cout << "moving maze ... " << std::endl;

    maze.move(120, 90);

    int Frame = 0;

    std::cout << "starting main loop ... " << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // TODO: mouse click!
            // if (event.type == sf::Mouse::isButtonPressed(sf::Mouse::Left))


            gui.handleEvent(event);
        }

        tgui::Callback callback;
        while (gui.pollCallback(callback))
        {
            if (callback.id == 1)
                window.close();

            else if (callback.id == 2)
            {
                if (callback.text == "Exit")
                    window.close();
            }
        }





        window.clear();

        maze.drawMaze(&window);

        control.updateInfo();

        gui.draw();

        window.display();
        std::cout << "Frame: " << Frame << std::endl;
        Frame++;
    }

    return 0;
}