#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>


int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    sf::Texture texture;
    std::cout<<"there's no error yet..."<<std::endl<<time(NULL)<<std::endl;
    if (!texture.loadFromFile("cb.bmp")) {
        std::cout<<"failed to load!"<<std::endl<<time(NULL)<<std::endl;
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(sprite);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
