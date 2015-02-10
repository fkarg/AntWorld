#include <SFML/Graphics.hpp>
#include <iostream>
#include "maze.hpp"
#include <vector>

using namespace std;
using namespace sf;



int main()
{
    // Create the main window
    RenderWindow app(VideoMode(800, 600), "SFML window");

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
    while (app.isOpen())
    {
        // Process events
        Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        cout << "gonna draw it ..." << endl;

        // Clear screen
        app.clear();

        // drawing the Maze
        maze.drawMaze(&app);

        // Update the window
        app.display();

        // shows the Frame number
        cout << "Frame: " << Frame << endl;
        Frame++;
    }

    return EXIT_SUCCESS;
}






// TODO: End!