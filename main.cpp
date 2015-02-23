#include <SFML/Graphics.hpp>
#include <iostream>
#include "maze.hpp"
#include "mazecreator.hpp"

using namespace std;
using namespace sf;



int main()
{
    // Create the main window
    RenderWindow window(VideoMode(620, 620), "SFML window");

    // Load a sprite to display
    // Texture texture;
    // cout << "there's no error yet..." << endl;
    // if (!texture.loadFromFile("cb.bmp")) {
    //     cout << "failed to load!" << endl;
    //     return EXIT_FAILURE;
    // }
    // Sprite sprite(texture);

    cout << "creating the maze ..." << endl;

    // Creating a 20 x 20 Maze
    Maze maze(20, 20);

    MazeCreator creator;

    cout << "MazeCreator created and adding Maze ..." << endl;

    creator.setMaze(&maze);

    creator.setStart(4, 0);

    cout << "Set start to x: 4 and y: 0" << endl;

    // thread creatorThread(creator.PrimsAlgorithm());
    // creatorThread.detach();

    cout << "trying Prim's Algorithm ..." << endl;

    creator.PrimsAlgorithm();

    cout << "end of Prim's Algorithm" << endl;

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

        // Update the window
        window.display();

        // shows the Frame number
        cout << "Frame: " << Frame << endl;
        Frame++;
    }

    return EXIT_SUCCESS;
}






// TODO: End!