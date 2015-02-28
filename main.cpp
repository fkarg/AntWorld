#include <SFML/Graphics.hpp>
#include <iostream>
#include "maze.hpp"
#include "mazecreator.hpp"

using namespace std;
using namespace sf;



void initAlgorithm(Maze *maze) {
    MazeCreator creator;

    cout << "MazeCreator created and adding Maze ..." << endl;

    creator.setMaze(maze);

    creator.setStart(4, 0);

    cout << "Set start to x: 4 and y: 0" << endl;

    // thread creatorThread(creator.PrimsAlgorithm());
    // creatorThread.detach();

    cout << "trying Prim's Algorithm ..." << endl;

    creator.PrimsAlgorithm();

    cout << "end of Prim's Algorithm" << endl;
}






int main()
{
    // Create the main window
    RenderWindow window(VideoMode(660, 660), "SFML window");

    cout << "creating the maze ..." << endl;

    // Creating a 20 x 20 Maze
    Maze maze(10, 10);

    bool once = false;

    // Tile tile;
//
    // tile.setIndex(0);
//
    // tile.setSize(620, 620, 30, 30);

    // Frame-counter
    int Frame = 0;

	// Start the game loop
    while (window.isOpen())
    {
        // Process events
        Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        cout << "gonna draw it ..." << endl;

        // Clear screen
        window.clear();

        // drawing the Maze
        maze.drawMaze(&window);

        // tile.drawTile(&window);
        // tile.drawWalls(&window);

        // Update the window
        window.display();

        // shows the Frame number
        cout << "Frame: " << Frame << endl;
        Frame++;

        if (!once) {
            initAlgorithm(&maze);
            once = true;
        }

    }

    return EXIT_SUCCESS;
}



