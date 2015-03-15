#include <TGUI/TGUI.hpp>
#include "GraphicsControl.hpp"
#include "ant.h"



#ifdef DEBUG
#define SOURCES /home/bz/ClionProjects/AntWorld/resources
#else
#define SOURCES "/home/bz/ClionProjects/AntWorld/resources/"
#endif



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

    Vector2i mousePosition;

    std::cout << "starting main loop ... " << std::endl;


    // WHILE the main window is open ...
    while (window.isOpen() )
    {
        // actualizing the vector of the mousePosition
        mousePosition = Mouse::getPosition(window);

        sf::Event event;

        while (window.pollEvent(event))
        {
            switch(event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    // exit the window if 'Escape'
                    if(event.key.code == Keyboard::Escape) {
                        cout << "Escape" << endl;
                        window.close();
                    }

                    // change the walls if a key for direction is
                    // pressed

                    if(Keyboard::isKeyPressed(Keyboard::Up))
                        control.changeWalls(0, control.isAdvancedMode() );

                    if(Keyboard::isKeyPressed(Keyboard::Right))
                        control.changeWalls(1, control.isAdvancedMode() );

                    if(Keyboard::isKeyPressed(Keyboard::Down))
                        control.changeWalls(2, control.isAdvancedMode() );

                    if(Keyboard::isKeyPressed(Keyboard::Left))
                        control.changeWalls(3, control.isAdvancedMode() );

                    // for the ASDW - Keys:
                    // but not changing the selected tile

                    if(Keyboard::isKeyPressed(Keyboard::W))
                        control.changeWalls(0);

                    if(Keyboard::isKeyPressed(Keyboard::D))
                        control.changeWalls(1);

                    if(Keyboard::isKeyPressed(Keyboard::S))
                        control.changeWalls(2);

                    if(Keyboard::isKeyPressed(Keyboard::A))
                        control.changeWalls(3);


                    // for moving the ant

                    if(Keyboard::isKeyPressed(Keyboard::I) )
                        ant.move(0);

                    if(Keyboard::isKeyPressed(Keyboard::L) )
                        ant.move(1);

                    if(Keyboard::isKeyPressed(Keyboard::K) )
                        ant.move(2);

                    if(Keyboard::isKeyPressed(Keyboard::J) )
                        ant.move(3);

                    break;
                case Event::TextEntered:break;
                case Event::KeyReleased:break;
                case Event::MouseButtonPressed:
                    // 'select' the clicked tile
                    if (Mouse::isButtonPressed(Mouse::Left) ) {
                        Tile *testPtr = NULL;
                        testPtr = maze.getTileClicked(mousePosition.x, mousePosition.y);
                        if (testPtr != NULL) {
                            control.changeTextInfoLabel(testPtr);
                        }
                    }
                    break;
                case Event::MouseButtonReleased:break;
                case Event::MouseMoved:break;
                default:
                    cout << "uncovered event" << endl;
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
                    cout << "uncought callback: " << to_string(callback.id) << endl;
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



