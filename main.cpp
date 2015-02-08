#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;




class Tile {

    private:
        int locX, locY, height, width;
        RectangleShape rect;

    public:
        void setSize(int x, int y, int height2, int width2){
            locX = x;
            locY = y;
            height = height2;
            width = width2;
            rect.setSize(Vector2f(height, width));
            rect.setFillColor(Color::Blue);
        }
        void drawTile(RenderWindow *renderWindow){
            renderWindow->draw(rect);
        }

};



class Maze {

    private:
        int sizeX = -1, sizeY = -1;
        Tile tile1;

    public:
        Maze(int xSize, int ySize){
            sizeX = xSize;
            sizeY = ySize;
            // TODO: placing tiles
            tile1.setSize(10, 10, 20, 20);
        }
        void drawMaze(RenderWindow *renderWindow){
            // TODO: draw Tiles!
        }
};






















int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    sf::Texture texture;
    std::cout << "there's no error yet..." << std::endl << time(NULL) << std::endl;
    if (!texture.loadFromFile("cb.bmp")) {
        std::cout << "failed to load!" << std::endl << time(NULL) << std::endl;
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);

    Maze maze(10, 10);

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
        maze.drawMaze(&app);

        // Update the window
        app.display();
        std::cout << "FRAME!" << std::endl;
    }

    return EXIT_SUCCESS;
}






