#include <TGUI/TGUI.hpp>
#include "GraphicsControl.hpp"
#include "mazecreator.hpp"

#define THEME_CONFIG_FILE "resources/Black.conf"



showTile tileToShow;

void initAlgorithm(Maze *maze) {
    MazeCreator creator;

    std::cout << "MazeCreator created and adding Maze ..." << std::endl;

    creator.setMaze(maze);

    creator.setStart(4, 0);

    std::cout << "Set start to x: 4 and y: 0" << std::endl;

    // thread creatorThread(creator.PrimsAlgorithm());
    // creatorThread.detach();

    std::cout << "trying Prim's Algorithm ..." << std::endl;

    // creator.PrimsAlgorithm();

    std::cout << "end of Prim's Algorithm" << std::endl;
}





int main()
{

    std::cout << "creating the maze ..." << std::endl;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(660, 660), "SFML window");
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

    // Creating a 10 x 10 Maze
    Maze maze(10, 10);

    tileToShow.setSize(30, 30, 35, 35);

    control.changeTextInfoLabel(&tileToShow);

    std::cout << "moving maze ... " << std::endl;

    maze.move(120, 90);

    // Frame-counter
    int Frame = 0;

    Vector2i mousePosition;

    std::cout << "starting main loop ... " << std::endl;


    // WHILE the main window is open ...
    while (window.isOpen())
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

                    if(Keyboard::isKeyPressed(Keyboard::Up)) {
                        control.changeWalls(0);
                    }
                    if(Keyboard::isKeyPressed(Keyboard::Right)) {
                        control.changeWalls(1);
                    }
                    if(Keyboard::isKeyPressed(Keyboard::Down)) {
                        control.changeWalls(2);
                    }
                    if(Keyboard::isKeyPressed(Keyboard::Left)) {
                        control.changeWalls(3);
                    }

                    break;
                case Event::TextEntered:break;
                case Event::KeyReleased:break;
                case Event::MouseButtonPressed:
                    // 'select' the clicked tile
                    if (Mouse::isButtonPressed(Mouse::Left) ) {
                        Tile *testptr = NULL;
                        testptr = maze.getTileClicked(mousePosition.x, mousePosition.y);
                        if (testptr != NULL) {
                            tileToShow = testptr;
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
                    control.changeWalls(callback.id);
                    break;
                case 10:
                    window.close();
                    break;
                default:
                    cout << "uncought callback: " << to_string(callback.id) << endl;
            }

        }

        cout << "gonna draw it ..." << endl;

        // Clear screen
        window.clear();

        // drawing the Maze
        maze.drawMaze(&window);

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



