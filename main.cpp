#include <SFML/Graphics.hpp>
#include <iostream>
#include "maze.hpp"
#include <vector>

using namespace std;
using namespace sf;



int main()
{
    // Create the main window
    RenderWindow window(VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    // Texture texture;
    // cout << "there's no error yet..." << endl;
    // if (!texture.loadFromFile("cb.bmp")) {
    //     cout << "failed to load!" << endl;
    //     return EXIT_FAILURE;
    // }
    // Sprite sprite(texture);

    cout << "creating the maze ..." << endl;

    // Creating a 10 x 10 Maze
    Maze maze(10, 10);

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