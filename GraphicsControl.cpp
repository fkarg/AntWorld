#include "GraphicsControl.h"


GraphicsControl::GraphicsControl(sf::RenderWindow *window) {
    GraphicsControl::window = window;
    tileToShowPtr = &tileToShowTile;
    antToShowPtr = &antToShowAnt;

    tileToShowTile.setSize(30, 50, 35, 35);

    for (int dir = 0; dir < 4; dir++)
        directionsTile[dir].setSize(30 + (dir == 0 ? 6 : dir == 1 ? 35 : dir == 2 ? 6 : -23),
                50 + (dir == 0 ? -23 : dir == 1 ? 6 : dir == 2 ? 35 : 6) , 23, 23);

    antToShowPtr->setPosition(tileToShowPtr);
    antToShowPtr->setAnt(&selectedAnt);

    antToShowPtr->setVisible(false);


    base.setPosition(tileToShowPtr, 0.24);
    base.setPosition(tileToShowPtr->getOwnX(), tileToShowPtr->getOwnY(), 0.24);
    leaf.setPosition(tileToShowPtr);
    leaf.setProducing(true);

}


// adding the GUI in the main window once
void GraphicsControl::addGui(tgui::Gui *gui) {

    // button for closing the Window (for test purposes)
    tgui::Button::Ptr closeButton(*gui);
    closeButton->load(THEME_CONFIG_FILE);
    closeButton->setPosition(30, lowest + diff * 9);
    closeButton->setSize(60, 20);
    closeButton->setText("Close");
    closeButton->bindCallback(tgui::Button::LeftMouseClicked);
    closeButton->setCallbackId(10);


    // button for focusing on the ant
    tgui::Button::Ptr focusButton(*gui);
    focusButton->load(THEME_CONFIG_FILE);
    focusButton->setPosition(500, 70);
    focusButton->setSize(90, 20);
    focusButton->setText("Focus on Ant");
    focusButton->bindCallback(tgui::Button::LeftMouseClicked);
    focusButton->setCallbackId(13);

    focusAntButton = focusButton;


    // button for doing some Ticks
    tgui::Button::Ptr doTicksButton(*gui);
    doTicksButton->load(THEME_CONFIG_FILE);
    doTicksButton->setPosition(600, 70);
    doTicksButton->setSize(90, 20);
    doTicksButton->setText("One Tick");
    doTicksButton->bindCallback(tgui::Button::LeftMouseClicked);
    doTicksButton->setCallbackId(9);
    tickButton = doTicksButton;


    // label to show information about the selected Tile
    tgui::Label::Ptr infoLabel(*gui);
    infoLabel->load(THEME_CONFIG_FILE);
    infoLabel->setPosition(20, 130);
    infoLabel->setTextSize(12);
    infoLabel->setTextColor(sf::Color(20, 200, 200) );
    infoLabel->setText("Info:\n\nIndex:\nX:\nY:\n\nFood:");

    TileInfoLabel = infoLabel;


    // label to show information about the maybe visible Ant
    tgui::Label::Ptr antLabel(*gui);
    antLabel->load(THEME_CONFIG_FILE);
    antLabel->setPosition(100, 30);
    antLabel->setTextSize(12);
    antLabel->setTextColor(sf::Color(20, 200, 200) );
    antLabel->setText("AntInfo: ...");

    AntInfoLabel = antLabel;


    // button to change the state of the wall in upper direction to tho tile selected
    tgui::Button::Ptr buttonChangeWallUp(*gui);
    buttonChangeWallUp->load(THEME_CONFIG_FILE);
    buttonChangeWallUp->setPosition(15, lowest + diff * 2);
    buttonChangeWallUp->setSize(90, 20);
    buttonChangeWallUp->bindCallback(tgui::Button::LeftMouseClicked);
    buttonChangeWallUp->setCallbackId(0);
    buttonChangeWallUp->setText("ChangeWallsUp");


    // button to change the state of the wall right to the tile selected
    tgui::Button::Ptr buttonChangeWallRight(*gui);
    buttonChangeWallRight->load(THEME_CONFIG_FILE);
    buttonChangeWallRight->setSize(90, 20);
    buttonChangeWallRight->setPosition(15, lowest + diff * 3);
    buttonChangeWallRight->bindCallback(tgui::Button::LeftMouseClicked);
    buttonChangeWallRight->setCallbackId(1);
    buttonChangeWallRight->setText("ChangeWallRight");


    // button to change the state of the wall in lower direction to the tile selected
    tgui::Button::Ptr buttonChangeWallDown(*gui);
    buttonChangeWallDown->load(THEME_CONFIG_FILE);
    buttonChangeWallDown->setSize(90, 20);
    buttonChangeWallDown->setPosition(15, lowest + diff * 4);
    buttonChangeWallDown->bindCallback(tgui::Button::LeftMouseClicked);
    buttonChangeWallDown->setCallbackId(2);
    buttonChangeWallDown->setText("ChangeWallDown");


    // button to change the state of the wall left to the tile selected
    tgui::Button::Ptr buttonChangeWallLeft(*gui);
    buttonChangeWallLeft->load(THEME_CONFIG_FILE);
    buttonChangeWallLeft->setSize(90, 20);
    buttonChangeWallLeft->setPosition(15, lowest + diff * 5);
    buttonChangeWallLeft->bindCallback(tgui::Button::LeftMouseClicked);
    buttonChangeWallLeft->setCallbackId(3);
    buttonChangeWallLeft->setText("ChangeWallLeft");


    // button to change the state of the ticks - started, paused, stopped
    tgui::Button::Ptr startTicksButton(*gui);
    startTicksButton->load(THEME_CONFIG_FILE);
    startTicksButton->setSize(90, 20);
    startTicksButton->setPosition(500, 40);
    startTicksButton->setCallbackId(4);
    startTicksButton->bindCallback(tgui::Button::LeftMouseClicked);
    startTicksButton->setText("Start");

    ticksControl = startTicksButton;


    // checkbox if 'Jumping' is allowed
    tgui::Checkbox::Ptr checkBox(*gui);
    checkBox->load(THEME_CONFIG_FILE);
    checkBox->setPosition(15, lowest + 20);
    checkBox->setText("Moving");
    checkBox->setSize(20, 20);
    checkBox->check();

    advancedMode = checkBox;


    // setting the selected tile to a Home - tile
    tgui::Button::Ptr setHomeButton(*gui);
    setHomeButton->load(THEME_CONFIG_FILE);
    setHomeButton->setPosition(15, lowest + diff * 6);
    setHomeButton->setText("set Home");
    setHomeButton->setCallbackId(6);
    setHomeButton->bindCallback(tgui::Button::LeftMouseClicked);
    setHomeButton->setSize(90, 20);

    GraphicsControl::setHomeButton = setHomeButton;


    // the setResButton, for making any normal tile to a Resource-Tile
    tgui::Button::Ptr setResButton(*gui);
    setResButton->load(THEME_CONFIG_FILE);
    setResButton->setPosition(15, lowest + diff * 7);
    setResButton->setSize(90, 20);
    setResButton->setText("set Resource");
    setResButton->setCallbackId(12);
    setResButton->bindCallback(tgui::Button::LeftMouseClicked);

    GraphicsControl::setResButton = setResButton;


    // testConnectedButton, for searching if two tiles are connected
    tgui::Button::Ptr TestConnectedButton(*gui);
    TestConnectedButton->load(THEME_CONFIG_FILE);
    TestConnectedButton->setPosition(15, lowest + diff * 8);
    TestConnectedButton->setText("TestConnected");
    TestConnectedButton->setCallbackId(5);
    TestConnectedButton->bindCallback(tgui::Button::LeftMouseClicked);
    TestConnectedButton->setSize(90, 20);


    // slider for controlling the production rate of the RES or the ants from a base
    tgui::Slider::Ptr slider(*gui);
    slider->load(THEME_CONFIG_FILE);
    slider->setVerticalScroll(false);
    slider->setPosition(20, lowest);
    slider->setSize(80, 11);
    slider->setMinimum(0);
    slider->setMaximum(20);
    slider->setValue(0);
    slider->bindCallback(tgui::Slider::ValueChanged);
    slider->setCallbackId(7);

    GraphicsControl::slider = slider;

    tgui::Slider::Ptr slider2(*gui);
    slider2->load(THEME_CONFIG_FILE);
    slider2->setVerticalScroll(false);
    slider2->setPosition(600, 50);
    slider2->setSize(80, 11);
    slider2->setMinimum(0);
    slider2->setMaximum(5);
    slider2->setValue(1);
    slider2->bindCallback(tgui::Slider::ValueChanged);
    slider2->setCallbackId(8);
    tickSlider = slider2;


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
void GraphicsControl::changeTextInfoLabel(Tile* tile) {
    tileToShowTile = tile;

    for (int dir = 0; dir < 4; dir++)
        if (tile->isSurrounding(dir) )
            directionsTile[dir] = tile->getSurrounding(dir);

    std::cout << "GC: changeTextInfoLabel" << std::endl;

    if (tile->hasAnt() )
        antToShowPtr->setAnt(tile->getAnt() );
    else antToShowPtr->setVisible(false);

    std::cout << "GC: Ant is visible or not now" << std::endl;

    if (connect) {
        craver.setAim(tileToShowPtr->getTileToShow());
        craver.setEndColor(sf::Color::Green);
        craver.colorPath(sf::Color::Cyan);
        craver.searchAStar();

        connect = false;
    }
    changeFocus();
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

    for (int dir = 0; dir < 4; dir++)
        if (!tileToShowPtr->isWall(dir) )
            directionsTile[dir].draw(window);

    if (tileToShowPtr->getTileToShow() != NULL) {
        drawBase = tileToShowPtr->getTileToShow()->isBASE();
        drawLeaf = tileToShowPtr->getTileToShow()->isRES();
    }

    if (antToShowPtr->getVisible() ) {
        AntInfoLabel->setText("Dir: " + std::to_string(antToShowPtr->getDir() ) +
                "   ID: " + std::to_string(antToShowPtr->getAntShown()->getID() ) +
                "   Ticks living: " + std::to_string(antToShowAnt.getAntShown()->getTicksLiving() ) +
                "   Food: " + std::to_string(antToShowAnt.getAntShown()->getFood() ) +
                "   \nTeam: " + std::to_string(antToShowPtr->getAntShown()->getTeamNum() ) +
                "   Ants on Tile: " + std::to_string(tileToShowTile.getTileToShow()->getAntCount() ) );
        if (focusAntButton->getText() == "End Focus" )
            AntInfoLabel->setText(AntInfoLabel->getText() + "\n\nFocused");
    } else AntInfoLabel->setText("Please select an Ant to show Info about it\n\n\nNo Ant Focused");
}


// testing if two tiles are connected, showing it in the GUI if they are
void GraphicsControl::testConnectedButtonClicked() {
    connect = true;
    craver.setStart(tileToShowPtr->getTileToShow() );
    craver.setStartColor(sf::Color::Yellow);
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


// resetting the color of the maze
void GraphicsControl::ResetColorOfMaze() {
	for (int i = 0; i < maze->getSizeX(); i++)
		for (int j = 0; j < maze->getSizeY(); j++)
			maze->getTile(i, j)->setColor(sf::Color(80, 80, 80, 200) );
}


// updates things according to the changed slider values
void GraphicsControl::sliderValueChanged() {
    if (!initial) {
        std::cout << "changed slider value" << std::endl;
        if (tileToShowTile.getTileToShow()->isRES()) {
            producing *res = tileToShowTile.getTileToShow()->getRes();
            res->setProductionRate((float) (slider->getValue() / 10.0));
        } else if (tileToShowTile.getTileToShow()->isBASE()) {
            int AntCount = tileToShowTile.getTileToShow()->getBase()->getAntCount();
            int sliderVal = slider->getValue();

            if (sliderVal != AntCount && AntCount < 20)
                tileToShowPtr->getTileToShow()->getBase()->addAnts(sliderVal - AntCount);
            changeTextInfoLabel(tileToShowPtr->getTileToShow());
        }
    }
}


// setting the right value to the tick-controlling button
void GraphicsControl::tickSliderChanged() {
    int val = tickSlider->getValue();
	std::cout << "changed TickSlider: " << val << std::endl;
	switch (val) {
		case 2:
			tickText = "Two";
			break;
		case 3:
			tickText = "Three";
			break;
		case 4:
			tickText = "Four";
			break;
		case 5:
			tickText = "Five";
			break;
		default:
			tickText = "No";
			break;
	}

    tickText += " Ticks";
    if (val == 1)
        tickText = "One Tick";

    tickButton->setText(tickText);
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
            doTick();
            if (move)
                changeTextInfoLabel(tileToShowPtr->getSurrounding(dir) );
        }
    }
}


// changing the shown text on the ticksControl Button
void GraphicsControl::TicksControlChangeState() {
    std::cout << "doing ticks ..." << std::endl;
    if (ticksControl->getText() == "Start" || ticksControl->getText() == "Resume")
        ticksControl->setText("Faster"), ticking = true;
    else if (ticksControl->getText() == "Faster")
        ticksControl->setText("Pause");
    else {
        ticksControl->setText("Resume");
        ticking = false;
    }
    doTick();
    // TODO: tickscontrol ...
}


// drawing the Ants from the base and the showAnt
void GraphicsControl::drawSpecial() {
    initial = true;

    if (drawBase || drawLeaf) {
        slider->show();

        if (drawLeaf) {
            setResButton->setText("Remove Res");
            slider->setValue( (unsigned int) (tileToShowTile.getTileToShow()->getRes()->getProductionRate() * 10.0) );
            leaf.draw(window);
        }
        if (drawBase) {
            base.setColor(base.getTile()->getBase()->getColor() );
            setHomeButton->setText("Remove Home");
            if (!drawLeaf) slider->setValue( (unsigned int) tileToShowTile.getTileToShow()->getBase()->getAntCount() );
            base.draw(window);
        }
    } else slider->hide();
    if (!drawBase)
        setHomeButton->setText("set Home");
    if (!drawLeaf)
        setResButton->setText("set Resource");

    initial = false;
    selectedAnt.draw(window);
    antToShowPtr->draw(window);
}


// returns the currently in the showTile selected tile
Tile* GraphicsControl::getTileSelected() {
    return tileToShowPtr->getTileToShow();
}


// toggles the focus of the ant currently selected
void GraphicsControl::changeFocus() {
    if (focusAntButton->getText() == "Focus on Ant" && getTileSelected() != NULL) {
        if (getTileSelected()->hasAnt() )
            focusedAnt = getTileSelected()->getAnt(), focusAntButton->setText("End Focus");
        else std::cout << "No Ant on Tile!!!" << std::endl;
    } else if (focusAntButton->getText() == "End Focus")
        focusAntButton->setText("Focus on Ant");
    else std::cout << "Please select a Tile first!!!" << std::endl;
}


// putting a colored layer over the maze from the view of the @param ant
void GraphicsControl::ColorFor(Ant* ant) {
	for (int i = 0; i < maze->getSizeX(); i++)
		for (int j = 0; j < maze->getSizeY(); j++) {
			Tile* toColor = maze->getTile(i, j);
			int rcol = 60, gcol = 60, bcol = 60;
			if (toColor->hasAnt() ) {
				if (ant->isInTeam(toColor->getAnt()->getID() ) )
					gcol += 100;
				else rcol += 130;
			}

			if (toColor->isRES() )
				gcol += 200;

            if (ant->isInTeam( (unsigned int) toColor->getScentID() )
                    && toColor->getScent() >= 0 )
                gcol += toColor->getScent();
            else rcol += toColor->getScent();

            rcol = rcol > 255 ? 255 : rcol;
            gcol = gcol > 255 ? 255 : gcol;
            bcol = bcol > 255 ? 255 : bcol;

			toColor->setColor(sf::Color(
                    (sf::Uint8) rcol, (sf::Uint8) gcol, (sf::Uint8) bcol) );

			if (toColor->isBASE())
                toColor->setColor(toColor->getBase()->getTeamNum() == ant->getTeamNum() ?
                                  sf::Color(20, 255, 20) : sf::Color(200, 20, 20) );
				// toColor->setColor(toColor->getBase()->getColor() );
		}
    maze->getTile(ant->getCurrent()->getIndex())->setColor(sf::Color::White);
}


// doing the Tick for everything on the map
void GraphicsControl::doTick() {

    std::cout << "Doing a Tick" << std::endl;

    if (ticking) {
        maze->doTick();
        selectedAnt.doTick();
        base.doTick();
        leaf.doTick();
        antToShowAnt.doTick();
    }

    for (int dir = 0; dir < 4 && tileToShowTile.getTileToShow() != NULL; dir++)
        if (tileToShowTile.getTileToShow()->isSurrounding(dir) )
            directionsTile[dir] = tileToShowTile.getTileToShow()->getSurrounding(dir);


    // focusing the ant if it got selected
    if (focusAntButton->getText() == "End Focus") {
        tileToShowTile = focusedAnt->getCurrent();
        antToShowAnt.setAnt(focusedAnt);

        if (focusedAnt->getDead() )
            focusAntButton->setText("Focus Ant");
        }
    ResetColorOfMaze();
    if (focusedAnt != NULL) ColorFor(focusedAnt);

    // slowing it down if the option to go faster is still present
    if (ticksControl->getText() == "Faster")
        std::this_thread::__sleep_for(std::chrono::seconds(0), std::chrono::milliseconds(60) );
}


// doing the @param number of ticks
void GraphicsControl::doTicks() {
    std::cout << "doing Ticks" << std::endl;
    int ticksNum = tickSlider->getValue();
    ticking = true;
	for (int i = 0; i < ticksNum; i++)
		doTick();
    ticking = false;
}




