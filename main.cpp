/// #include <SFML/Graphics.hpp>
/// #include <iostream>
/// //// #include "maze.hpp"
/// //// #include "GraphicsControl.hpp"
/// #include <TGUI/TGUI.hpp>
/// 
/// #define THEME_CONFIG_FILE "resources/Black.conf"
/// 
/// 
/// using namespace std;
/// using namespace sf;
/// 
/// 
/// 
/// int main()
/// {
///     // Create the main window
///     RenderWindow window(VideoMode(800, 600), "SFML window");
/// 
///     //// GraphicsControl graphicsTGUI;
/// 
///     tgui::Gui gui;
/// 
///     if (!gui.setGlobalFont("resources/DejaVuSans.ttf"))
///         return 1;
/// 
///     tgui::Picture::Ptr picture(gui);
///     picture->load("resources/Black.png");
/// 
/// 
///     //// graphicsTGUI.create(window);
/// 
///     // ...
/// 
/// 
///     cout << "gonna create d buttöööön " << endl;
/// 
/// 
///     tgui::Button::Ptr button(gui);
///     button->load(THEME_CONFIG_FILE);
///     button->setPosition(40, 25);
///     button->setText("Quit");
///     button->setCallbackId(1);
///     button->bindCallback(tgui::Button::LeftMouseClicked);
///     button->setSize(300, 40);
/// 
///     cout << "created button" << endl;
/// 
///     // Load a sprite to display
///     // Texture texture;
///     // cout << "there's no error yet..." << endl;
///     // if (!texture.loadFromFile("cb.bmp")) {
///     //     cout << "failed to load!" << endl;
///     //     return EXIT_FAILURE;
///     // }
///     // Sprite sprite(texture);
/// 
///     //// cout << "creating the maze ..." << endl;
/// 
///     // Creating a 10 x 10 Maze
///     //// Maze maze(10, 10);
/// 
///     // Frame-counter
///     int Frame = 0;
/// 
/// 	// Start the game loop
///     while (window.isOpen())
///     {
///         // Process events
///         Event event;
///         while (window.pollEvent(event))
///         {
///             // Close window : exit
///             if (event.type == sf::Event::Closed)
///                 window.close();
/// 
///             //// graphicsTGUI.handleEvent(event);
///             gui.handleEvent(event);
///         }
/// 
///         cout << "creating callback" << endl;
/// 
///         tgui::Callback callback;
/// 
///         while(gui.pollCallback(callback)){
///             if (callback.id == 1)
///                 window.close();
/// 
///             else if (callback.id == 2)
///             {
///                 if (callback.text == "Exit")
///                     window.close();
///             }
///         }
/// 
///         //// while(graphicsTGUI.pollCallback(callback)){
///         ////     if(callback.id == 1)
///         ////         window.close();
///         //// }
/// 
///         cout << "clearing the window ..." << endl;
/// 
///         // Clear screen
///         window.clear();
/// 
///         // drawing the Maze
///         //// maze.drawMaze(&window);
/// 
///         //// graphicsTGUI.draw();
/// 
///         cout << "drawing gui ..." << endl;
/// 
///         gui.draw();
/// 
///         cout << "displaying it ... " << endl;
/// 
///         // Update the window
///         window.display();
/// 
///         // shows the Frame number
///         cout << "Frame: " << Frame << endl;
///         Frame++;
///     }
/// 
///     return EXIT_SUCCESS;
/// }
/// 
/// 
/// 
/// 


#include <TGUI/TGUI.hpp>
#include "GraphicsControl.hpp"
#include "maze.hpp"

#define THEME_CONFIG_FILE "resources/Black.conf"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "TGUI window");
    tgui::Gui gui(window);

    if (!gui.setGlobalFont("resources/DejaVuSans.ttf"))
        return 1;

    /// tgui::Picture::Ptr picture(gui);
    /// picture->load("resources/Black.png");

    tgui::Button::Ptr button(gui);
    button->load(THEME_CONFIG_FILE);
    button->setPosition(40, 25);
    button->setText("Button1");
    button->setCallbackId(1);
    button->bindCallback(tgui::Button::LeftMouseClicked);
    button->setSize(300, 40);

    Maze maze(10, 10);

    maze.move(40, 90);

    int Frame = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

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

        gui.draw();
        window.display();
        std::cout << "Frame: " << Frame << std::endl;
        Frame++;
    }

    return 0;
}