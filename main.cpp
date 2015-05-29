#include <TGUI/TGUI.hpp>
#include "GraphicsControl.h"


#define SOURCES "/usr/resources_coding/"



int main()
{

    std::cout << "creating the maze ..." << std::endl;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(760, 750), "SFML window");
    tgui::Gui gui(window);

    std::cout << "setting global font ..." << std::endl;

    if (!gui.setGlobalFont(SOURCES"DejaVuSans.ttf"))
        return 1;


    std::cout << "creating Button ..." << std::endl;

    // creating the GraphicsControl
    GraphicsControl control (&window);
    control.addGui(&gui);

    std::cout << "creating maze ... " << std::endl;

    // Creating a 10 x 10 Maze
    Maze maze(20, 20);

    std::cout << "moving maze ... " << std::endl;

    maze.move(120, 110);

    control.setMaze(&maze);

    // Frame-counter
    int Frame = 0;

    sf::Vector2i mousePosition;

    std::cout << "starting main loop ... " << std::endl;


    // WHILE the main window is open ...
    while (window.isOpen() )
    {
        // actualizing the vector of the mousePosition
        mousePosition = sf::Mouse::getPosition(window);

        sf::Event event;

        while (window.pollEvent(event))
        {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    // exit the window if 'Escape'
                    if(event.key.code == sf::Keyboard::Escape) {
                        std::cout << "Escape" << std::endl;
                        window.close();
                    }

                    // change the walls if a key for direction is
                    // pressed

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        control.changeWalls(0, control.isAdvancedMode() );

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                        control.changeWalls(1, control.isAdvancedMode() );

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        control.changeWalls(2, control.isAdvancedMode() );

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                        control.changeWalls(3, control.isAdvancedMode() );

                    // for the ASDW - Keys:
                    // but not changing the selected tile

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
                        control.changeWalls(0);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        control.changeWalls(1);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
                        control.changeWalls(2);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
                        control.changeWalls(3);


                    // for moving the ant

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::G) )
                        control.AntMove(0);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::T) )
                        control.AntMove(1);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) )
                        control.AntMove(2);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::N) )
                        control.AntMove(3);

                    break;
                case sf::Event::TextEntered:break;
                case sf::Event::KeyReleased:break;
                case sf::Event::MouseButtonPressed:
                    // 'select' the clicked tile
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
                        Tile *testPtr = NULL;
                        testPtr = maze.getTileClicked(mousePosition.x, mousePosition.y);
                        if (testPtr != NULL) {
                            control.changeTextInfoLabel(testPtr);
                        }
                    }
                    break;
                case sf::Event::MouseButtonReleased:break;
                case sf::Event::MouseMoved:break;
                default:
                    std::cout << "uncovered event" << std::endl;
            }

            gui.handleEvent(event);
        }

        tgui::Callback callback;
        while (gui.pollCallback(callback))
        {
            // catches the callback of the buttons
            switch (callback.id) {
                case 0:
                case 1:
                case 2:
                case 3:
                    control.changeWalls(callback.id, control.isAdvancedMode() );
                    std::cout << "changeWallDir: " << std::to_string(callback.id) << std::endl;
                    break;
                case 4:
                    control.TicksControlChangeState();
                    break;
                case 5:
                    control.testConnectedButtonClicked();
                    break;
                case 6:
                    maze.setHome(control.getTileSelected() );
                    break;
                case 7:
                    control.sliderValueChanged();
                    break;
                case 10:
                    std::cout << "closing window" << std::endl;
                    window.close();
                    break;
                case 11:
                    if (callback.text == "Exit")
                        window.close();
                    else
                        control.handleCallback(callback);
                    break;
                case 12:
                    maze.setRes(control.getTileSelected() );
                    break;
                default:
                    std::cout << "uncought callback: " << std::to_string(callback.id) << std::endl;
                    break;
            }
        }

        // Clear screen
        window.clear();

        // updating the InfoPanel
        control.updateInfo();

        // drawing the Maze
        maze.drawMaze(&window);

        control.drawAnts();

        // drawing the gui
        gui.draw();

        // displaying it
        window.display();
        std::cout << "Frame: " << Frame << std::endl;
        Frame++;

    }

    return EXIT_SUCCESS;
}



