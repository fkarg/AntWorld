#include "GraphicsControl.h"


GraphicsControl::GraphicsControl(sf::RenderWindow *window) {
    GraphicsControl::window = window;
    tileToShowPtr = &tileToShowTile;
    antToShowPtr = &antToShowAnt;

    tileToShowTile.setSize(30, 50, 35, 35);

    antToShowPtr->setPosition(tileToShowPtr);
    antToShowPtr->setAnt(&selectedAnt);

    antToShowPtr->setVisible(false);


    base.setPosition(tileToShowPtr->getOwnX(), tileToShowPtr->getOwnY(), 0.24);

}


// adding the GUI in the main window once
void GraphicsControl::addGui(tgui::Gui *gui) {

    // button for closing the Window (for test purposes)
    tgui::Button::Ptr button(*gui);
    button->load(THEME_CONFIG_FILE);
    button->setPosition(20, 570);
    button->setSize(60, 20);
    button->setText("Close");
    button->bindCallback(tgui::Button::LeftMouseClicked);
    button->setCallbackId(10);


    // label to show information about the selected Tile
    tgui::Label::Ptr infoLabel(*gui);
    infoLabel->load(THEME_CONFIG_FILE);
    infoLabel->setPosition(20, 115);
    infoLabel->setTextSize(12);
    infoLabel->setTextColor(sf::Color(20, 200, 200) );
    infoLabel->setText("Info:\n\nIndex:\nX:\nY:\n\nFood:");

    TileInfoLabel = infoLabel;


    // label to show information about the maybe visible Ant
    tgui::Label::Ptr antLabel(*gui);
    antLabel->load(THEME_CONFIG_FILE);
    antLabel->setPosition(100, 35);
    antLabel->setTextSize(12);
    antLabel->setTextColor(sf::Color(20, 200, 200) );
    antLabel->setText("AntInfo: ...");

    AntInfoLabel = antLabel;


    // button to change the state of the wall in upper direction to tho tile selected
    tgui::Button::Ptr buttonChangeWallUp(*gui);
    buttonChangeWallUp->load(THEME_CONFIG_FILE);
    buttonChangeWallUp->setPosition(15, 360);
    buttonChangeWallUp->setSize(90, 20);
    buttonChangeWallUp->bindCallback(tgui::Button::LeftMouseClicked);
    buttonChangeWallUp->setCallbackId(0);
    buttonChangeWallUp->setText("ChangeWallsUp");


    // button to change the state of the wall right to the tile selected
    tgui::Button::Ptr buttonChangeWallRight(*gui);
    buttonChangeWallRight->load(THEME_CONFIG_FILE);
    buttonChangeWallRight->setSize(90, 20);
    buttonChangeWallRight->setPosition(15, 390);
    buttonChangeWallRight->bindCallback(tgui::Button::LeftMouseClicked);
    buttonChangeWallRight->setCallbackId(1);
    buttonChangeWallRight->setText("ChangeWallRight");


    // button to change the state of the wall in lower direction to the tile selected
    tgui::Button::Ptr buttonChangeWallDown(*gui);
    buttonChangeWallDown->load(THEME_CONFIG_FILE);
    buttonChangeWallDown->setSize(90, 20);
    buttonChangeWallDown->setPosition(15, 420);
    buttonChangeWallDown->bindCallback(tgui::Button::LeftMouseClicked);
    buttonChangeWallDown->setCallbackId(2);
    buttonChangeWallDown->setText("ChangeWallDown");


    // button to change the state of the wall left to the tile selected
    tgui::Button::Ptr buttonChangeWallLeft(*gui);
    buttonChangeWallLeft->load(THEME_CONFIG_FILE);
    buttonChangeWallLeft->setSize(90, 20);
    buttonChangeWallLeft->setPosition(15, 450);
    buttonChangeWallLeft->bindCallback(tgui::Button::LeftMouseClicked);
    buttonChangeWallLeft->setCallbackId(3);
    buttonChangeWallLeft->setText("ChangeWallLeft");


    // button to change the state of the ticks - started, paused, stopped
    tgui::Button::Ptr startTicksButton(*gui);
    startTicksButton->load(THEME_CONFIG_FILE);
    startTicksButton->setSize(90, 20);
    startTicksButton->setPosition(500, 50);
    startTicksButton->setCallbackId(4);
    startTicksButton->setText("Start");


    // checkbox if 'Jumping' is allowed
    tgui::Checkbox::Ptr checkBox(*gui);
    checkBox->load(THEME_CONFIG_FILE);
    checkBox->setPosition(15, 320);
    checkBox->setText("Moving");
    checkBox->setSize(20, 20);
    checkBox->check();

    advancedMode = checkBox;


    // setting the selected tile to a Home - tile
    tgui::Button::Ptr setHomeButton(*gui);
    setHomeButton->load(THEME_CONFIG_FILE);
    setHomeButton->setPosition(15, 480);
    setHomeButton->setText("set Home");
    setHomeButton->setCallbackId(6);
    setHomeButton->bindCallback(tgui::Button::LeftMouseClicked);
    setHomeButton->setSize(90, 20);

    GraphicsControl::setHomeButton = setHomeButton;


    // the setResButton, for making any normal tile to a Resource-Tile
    tgui::Button::Ptr setResButton(*gui);
    setResButton->load(THEME_CONFIG_FILE);
    setResButton->setPosition(15, 510);
    setResButton->setSize(90, 20);
    setResButton->setText("set Resource");
    setResButton->setCallbackId(12);
    setResButton->bindCallback(tgui::Button::LeftMouseClicked);

    GraphicsControl::setResButton = setResButton;

    // testConnectedButton, for searching if two tiles are connected
    tgui::Button::Ptr TestConnectedButton(*gui);
    TestConnectedButton->load(THEME_CONFIG_FILE);
    TestConnectedButton->setPosition(15, 540);
    TestConnectedButton->setText("TestConnected");
    TestConnectedButton->setCallbackId(5);
    TestConnectedButton->bindCallback(tgui::Button::LeftMouseClicked);
    TestConnectedButton->setSize(90, 20);


    // TODO: implement bar to set the production of ... whatever (Food, Res, etc) or the number of ants

    tgui::Slider::Ptr slider(*gui);
    slider->load(THEME_CONFIG_FILE);
    slider->setVerticalScroll(false);
    slider->setPosition(20, 300);
    slider->setSize(80, 11);
    slider->setMinimum(0);
    slider->setMaximum(20);
    slider->setValue(0);
    slider->bindCallback(tgui::Slider::ValueChanged);
    slider->setCallbackId(7);

    GraphicsControl::slider = slider;


    // creating the menu
    tgui::MenuBar::Ptr menu(*gui);
    menu->load(THEME_CONFIG_FILE);
    menu->setSize(window->getSize().x, 20);

    menu->addMenu("Maze");
    menu->addMenuItem("Maze", "Reset");
    menu->addMenuItem("Maze", "Create Random");
    menu->addMenuItem("Maze", "Create Perfect");

    menu->addMenu("File");
    menu->addMenuItem("File", "Load");
    menu->addMenuItem("File", "Save");
    menu->addMenuItem("File", "Exit");

    menu->bindCallback(tgui::MenuBar::MenuItemClicked);
    menu->setCallbackId(11);


}


// setting the maze for the craver, the perfectCreator and the randomCreator
void GraphicsControl::setMaze(Maze *maze) {
    GraphicsControl::maze = maze;
    craver.setMaze(maze);
    perf.setMaze(maze);
    randomCreator.setMaze(maze);

    selectedAnt.setPosition(maze->getTile(rand() % maze->INDEX_MAX() ) );
}


// changing the TileInfoLabel to the @param tile
void GraphicsControl::changeTextInfoLabel(Tile *tile) {
    tileToShowTile = tile;

    std::cout << "GC: changeTextInfoLabel" << std::endl;

    if (tile->hasAnt() )
        antToShowPtr->setAnt(tile->getAnt() );
    else antToShowPtr->setVisible(false);

    std::cout << "GC: Ant is visible or not now" << std::endl;

    if (connect) {
        craver.setAim(tileToShowPtr->getTileToShow());
        craver.colorPath(sf::Color::Cyan);
        craver.searchAStar();

        connect = false;
    }
}


// moving the currently selected Ant
void GraphicsControl::AntMove(int dir) {
    if (antToShowPtr->getVisible() ) {
        std::cout << "Moving Ant " << antToShowPtr->getAntShown()->getID()
                << " in dir: " << dir << " on Tile: " << tileToShowPtr->getIndex() << std::endl;
        antToShowAnt.move(dir);
        if (!tileToShowPtr->isWall(dir) )
            changeTextInfoLabel(tileToShowPtr->getSurrounding(dir));
    }
}


// updating the TileInfoLabel and the separately displayed Tile
void GraphicsControl::updateInfo() {
    tileToShowPtr->doTick();

    TileInfoLabel->setText(tileToShowPtr->getTileInfo() );
    tileToShowPtr->draw(window);

    if (tileToShowPtr->getTileToShow() != NULL) {
        drawBase = tileToShowPtr->getTileToShow()->isBASE();
        drawLeaf = tileToShowPtr->getTileToShow()->isRES();
    }

    if (antToShowPtr->getVisible() ) {
        AntInfoLabel->setText("Dir: " + std::to_string(antToShowPtr->getDir() ) +
                "\nID: " + std::to_string(antToShowPtr->getAntShown()->getID() - 21) +
                "\nTeam: " + std::to_string(antToShowPtr->getAntShown()->getTeamNum() ) );
    } else AntInfoLabel->setText("Please select an Ant to show Info about it");
}


// testing if two tiles are connected, showing it in the GUI if they are
void GraphicsControl::testConnectedButtonClicked() {
    connect = true;
    craver.setStart(tileToShowPtr->getTileToShow() );
}


// handling the callbacks from the menu
void GraphicsControl::handleCallback(tgui::Callback callback) {
    if (callback.id == 11) {
        std::cout << "Clicked at Menu" << std::endl;

        if (callback.text == "Reset")
            ResetMaze();
        if (callback.text == "Create Random")
            createRandom();
        if (callback.text == "Create Perfect")
            createPerfect();
    }
}


// letting the perfectCreator run
void GraphicsControl::createPerfect() {
    perf.start();
}


// creating a completely random maze
void GraphicsControl::createRandom() {
    randomCreator.reset();
    randomCreator.complete();
}


// resetting the maze a whole
void GraphicsControl::ResetMaze() {
    perf.ResetMaze();
}


// updates things according to the changed slider values
void GraphicsControl::sliderValueChanged() {
    std::cout << "changed slider value" << std::endl;
    int AntCount = tileToShowTile.getTileToShow()->getBase()->getAntCount();
    int sliderVal = slider->getValue();

    if (sliderVal != AntCount && AntCount < 20)
        tileToShowPtr->getTileToShow()->getBase()->addAnts(sliderVal - AntCount);
    changeTextInfoLabel(tileToShowPtr->getTileToShow() );
}


// returns if the Checkbox is checked or not
bool GraphicsControl::isAdvancedMode() {
    return advancedMode->isChecked();
}


// changes the state of the wall in @param dir
void GraphicsControl::changeWalls(int dir, bool move) {
    if (dir % 4 == dir && tileToShowPtr->getTileToShow() != NULL) {
        if (tileToShowPtr->isSurrounding(dir) ) {
            std::cout << "Changing wall in dir " << dir << " from " << tileToShowPtr->getTileToShow() << std::endl;
                        tileToShowPtr->setWall(dir, !tileToShowPtr->isWall(dir) );
            tileToShowPtr->getSurrounding(dir)->setWall( (dir + 2) % 4,
                    !tileToShowPtr->getSurrounding(dir)->isWall( (dir + 2) % 4) );
            if (move)
                changeTextInfoLabel(tileToShowPtr->getSurrounding(dir) );
        }
    }
}


// changing the shown text on the ticksControl Button
void GraphicsControl::TicksControlChangeState() {
    if (ticksControl->getText() == "Start" || ticksControl->getText() == "Resume")
        ticksControl->setText("Pause");
    else
        ticksControl->setText("Resume");
}


// drawing the Ants from the base and the showAnt
void GraphicsControl::drawAnts() {
    if (drawBase) {
        base.draw(window);
        slider->show();
        slider->setValue( (unsigned int) tileToShowTile.getTileToShow()->getBase()->getAntCount() );
        setHomeButton->setText("Remove Home");
    } else {
        slider->hide();
        setHomeButton->setText("set Home");
    }
    if (drawLeaf) {
        leaf.setProducing(true);
        slider->show();
        setResButton->setText("Remove Resource");
    } else {
        slider->hide();
        setResButton->setText("set Resource");
    }
    selectedAnt.draw(window);
    antToShowPtr->draw(window);
}


// returns the currently in the showTile selected tile
Tile* GraphicsControl::getTileSelected() {
    return tileToShowPtr->getTileToShow();
}


void GraphicsControl::doTick() {
    // for the implementation
}







