#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;


/*
 * Tile: the background is out of tiles
 *
 * setSize:
 * @param x: X-location of the Tile later on
 * @param y: Y-location of the Tile later on
 * @param height2: the height of the tile
 * @param width2: the width of the tile
 * (the 2 is there since the scope resolution operator didn't work for some reason)
 * setting the size, position and color of the rect
 *
 *
 * drawTile:
 * @param renderWindow: the window the rect is drawn in
 * drawing the rect
 */
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
            rect.setPosition(Vector2f(locX, locY));
        }
        void drawTile(RenderWindow *renderWindow){
            renderWindow->draw(rect);
        }

};


/*
 * Maze: including all the Tiles, used to manipulate only specific Tiles
 * @param xSize: how many tiles are gonna be in x direction
 * @param ySize: how many tiles are gonna be in y direction
 *
 * drawMaze:
 * @param renderWindow: needed for the Tile.drawTile method to draw on
 * drawing all Tiles in the MAP
 */
class Maze {

    private:
        int sizeX = -1, sizeY = -1;
        vector<vector<Tile> > MAP;

    public:
        Maze(int xSize, int ySize){
            sizeX = xSize;
            sizeY = ySize;
            for(int i = 0; i < xSize; i++){
                for(int j = 0; j < ySize; j++){
                    Tile tile;
                    tile.setSize(i * 35, j * 35, 30, 30);
                    // tile might not have been initialized?
                    MAP[i][j] = tile;
                }
            }
        }
        void drawMaze(RenderWindow *renderWindow){
            // TODO: draw Tiles!
            for(int i = 0; i < sizeX; i++){
                for(int j = 0; j < sizeY; j++){
                    MAP[i][j].drawTile(renderWindow);
                }
            }
        }
};



int main()
{
    // Create the main window
    RenderWindow app(VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    Texture texture;
    cout << "there's no error yet..." << endl;
    if (!texture.loadFromFile("cb.bmp")) {
        cout << "failed to load!" << endl;
        return EXIT_FAILURE;
    }
    Sprite sprite(texture);

    cout << "creating the maze ..." << endl;

    // Creating a 10 x 10 Maze
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

        cout << "gonna draw it ..." << endl;

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(sprite);

        // drawing the Maze
        maze.drawMaze(&app);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}






