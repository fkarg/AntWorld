#include <TGUI/TGUI.hpp>
#include "GraphicsControl.hpp"
#include "ant.h"



#define SOURCES "/home/bz/ClionProjects/AntWorld/resources/"



int main()
{

    std::cout << "creating the maze ..." << std::endl;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(660, 660), "SFML window");
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
    Maze maze(15, 15);

    RandomCreator randomCreator(&maze);
    control.setMaze(&maze);

    std::cout << "moving maze ... " << std::endl;

    maze.move(120, 90);

    Ant ant;

    ant.setPosition(maze.getTile(rand() % maze.INDEX_MAX() ) );

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

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                        control.changeWalls(0);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                        control.changeWalls(1);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                        control.changeWalls(2);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        control.changeWalls(3);


                    // for moving the ant

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::I) )
                        ant.move(0);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::L) )
                        ant.move(1);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::K) )
                        ant.move(2);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::J) )
                        ant.move(3);

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
                    break;
                case 4:
                    control.TicksControlChangeState();
                    break;
                case 5:
                    control.testConnectedButtonClicked();
                    break;
                case 6:
                    control.createPerfect();
                    break;
                case 7:
                    randomCreator.reset();
                    break;
                case 10:
                    window.close();
                    break;
                default:
                    std::cout << "uncought callback: " << std::to_string(callback.id) << std::endl;
                    break;
            }
        }

        if (Frame % 4 == 0)
            randomCreator.doTicks(10);

        // Clear screen
        window.clear();

        // drawing the Maze
        maze.drawMaze(&window);

        // drawing the ant TODO: AntController
        ant.draw(&window);

        // updating the InfoPanel
        control.updateInfo();

        // drawing the gui
        gui.draw();

        // displaying it
        window.display();
        std::cout << "Frame: " << Frame << std::endl;
        Frame++;

    }

    return EXIT_SUCCESS;
}



