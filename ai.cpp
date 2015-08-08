#include "ai.h"
#include "ant.h"



void Surrounding_state::print() const {
	std::cout << "Surrounding - INFO" << std::endl;
	std::cout << "Walls and Scent: " << std::endl;
	for (int dir = 0; dir < 4; dir++)
		std::cout << "Dir: " << dir << " wall: " << walls[dir]
			<< " scent: " << scents[4] << std::endl;

	std::cout << "isFood: " << isFood << " isBase: " << isBase
		<< " foodThere: " << foodThere << " antFood: " << antFood
		<< std::endl;
}


ai::ai() {
    srand((unsigned int) time(0) );
}

// sensing, reacting and moving
void ai::senseAndAct(Ant* itself) {
	// std::cout << "Ant " << itself->getID() << " is doing sth" << std::endl;
	DO(decide(sense(itself) ), itself);
}


// @returns the surrounding conditions around the @param ant
Surrounding_state ai::sense(Ant* ant) {
	Surrounding_state current;
	// testing the surroundings for walls and scents
	for (int dir = 0; dir < 4; dir++ ) {
		current.walls[dir] = ant->getCurrent()->isWall(dir);
		if (!current.walls[dir]) {
			current.scents[dir] = ant->getCurrent()->getScent();
			current.teamScent[dir] = ant->getCurrent()->getTeamScent(ant) > 0;
            current.scents2[dir] = ant->getCurrent()->getScent(2);
            current.teamScent2[dir] = ant->getCurrent()->getTeamScent(ant, 2) > 0;
            if (current.teamScent[dir] ) current.TeamScentCount += 1;
            if (current.teamScent2[dir] ) current.TeamScent2Count += 1;
		}
		if (ant->getCurrent()->isSurrounding(dir) && !ant->getCurrent()->isWall(dir) )
			if (ant->getCurrent()->getSurrounding(dir)->isBASE() )
				current.BaseInDir = dir;
			else if (ant->getCurrent()->getSurrounding(dir)->isRES() )
				current.FoodInDir = dir;
	}
	// what type the current tile is (except for hasAnt, since that has to be true)
	current.isBase = ant->getCurrent()->isBASE();
	if (current.isBase && ant->getCurrent()->getBase()->getTeamNum() == ant->getTeamNum() )
		current.isOwnBase = true;
	else current.isOwnBase = false;
	current.isFood = ant->getCurrent()->isFood() > 0;
	if (current.isFood)
		current.foodThere = ant->getCurrent()->isFood();
	current.antFood = ant->getFood();
	current.lastAction = ant->getLastAction();

	// based on the food-state searching for either the base, some food, or
	if (ant->getFood() > 15)
		current.searchingHome = true, ant->getCurrent()->addScent(ant);
	else if (ant->getFood() < 15)
		current.searchingFood = true;
    
    for (int num = 0; num < 3; num++)
        current.scentThere[num] = ant->getCurrent()->getScent(num),
            current.teamScentThere[num] = ant->getCurrent()->getTeamScent(ant, num) > 0;

	return current;
}


// the @return Action what to do based on the @param currentState
ACTION ai::decide(const Surrounding_state& currentState) {
    std::cout << "AI --- DECIDING" << std::endl;

	if (currentState.foodThere >= 1
			&& currentState.antFood <= MAX_FOOD_ANT_CARRYING - 2
			&& !currentState.isBase)
		return TAKE_FOOD;
	if (currentState.isOwnBase && currentState.antFood > 10)
		return GIVE_FOOD;
	if (currentState.isOwnBase && currentState.antFood < 10)
		return TAKE_FOOD;

	ACTION decision = STAY;

	// currentState.print();		// printing the currentState (dbgmode)

	int highest = 0, highestDir = -1, possDir = 0, lastDir = -1, teamDir = -1, lowestDir = -1, lowest = 255;

	// testing for the number of directions without walls and the direction with the highest and lowest scent
	for (int dir = 0; dir < 4; dir++) {
		if (currentState.lastAction != (dir + 2) % 4) {
			if (currentState.scents[dir] > highest && currentState.teamScent[dir])
				highest = currentState.scents[dir], highestDir = dir; // dirTo = dir;
			if (currentState.scents[dir] < lowest && currentState.teamScent[dir] && currentState.scents[dir] > 0)
				lowestDir = dir, lowest = currentState.scents[dir];
		}
		if (!currentState.walls[dir] )
			possDir++, lastDir = dir;
	}

	// testing if this is a dead end (and if there isn't food or sth keeping the ant here too, go away from it
	if (possDir == 1 && (lastDir + 2) % 4 != currentState.lastAction)
		decision = (ACTION) lastDir;

	// if there's only two directions possible, you came from one and will go to the other

	if (possDir == 2)
		if ( (lastDir + 2) % 4 != currentState.lastAction)
			decision = (ACTION) lastDir;
		else possDir += 1;

	// if there's more than two possibilities, a random event is being chosen for the time being
	if (possDir >= 3)
		while (decision == STAY) {
			int newDir = rand() % 4;
			if ( (newDir + 2) % 4 != currentState.lastAction
					&& !currentState.walls[newDir] )
                decision = (ACTION) newDir;
        }
    std::cout << "'random' decision was: " << decision << std::endl;

    // TODO: scent-integration
    // for one scent in a direction the ant didn't come from: follow it
    // for two scents, one from the dir the ant came from, follow the other
    // for two scents, both not from the dir the ant came from,
    //  follow the higher when searching the Home
    //  ant the lower one when searching food
    // for more than two, or one at the own tile too:
    //  the same as for two not from the current direction
    // if there's no scent follow the randowm choice aready made

//    bool decided = false;

    switch (currentState.TeamScentCount) {
        case 1:
            for (int dir = 0; dir < 4; dir++)
                if (currentState.teamScent[dir] && (dir + 2) % 4 != currentState.lastAction)
                    decision = (ACTION) dir, std::cout << "following only scent" << std::endl;
            break;
        case 2:
        case 3:
        case 4: {
            if ((highestDir + 2) % 4 != currentState.lastAction && currentState.searchingHome && highest > 0)
                decision = (ACTION) highestDir, std::cout << "following highest" << std::endl;
            else if ((lowestDir + 2) % 4 != currentState.lastAction && currentState.searchingFood && lowest < 255)
                decision = (ACTION) lowestDir, std::cout << "following lowest" << std::endl;
            else if (highest > 0 && lowest < 255) {
                int dirs[4] = {-1, -1, -1, -1}, tmpdir = -1, count = 0;
                for (int dir = 0; dir < 4; dir++)
                    if ((dir + 2) % 4 != currentState.lastAction && dir != highestDir && dir != lowestDir) {
                        dirs[1] = dirs[0] >= 0 && currentState.teamScent[dir] ? dirs[0] : dirs[1];
                        dirs[0] = currentState.teamScent[dir] ? dir : dirs[0];
                        count += currentState.teamScent[dir] ? 1 : 0;
                    }
                if (count == 0) {
                    if (currentState.searchingFood) decision = (ACTION) highestDir;
                    else if (currentState.searchingHome) decision = (ACTION) lowestDir;
                } else if (count == 1) {
                    decision = (ACTION) dirs[0];
                } else if (currentState.searchingHome)
                    decision = dirs[0] > dirs[1] ? (ACTION) dirs[0] : (ACTION) dirs[1];
                else if (currentState.searchingFood) decision = dirs[0] > dirs[1] ? (ACTION) dirs[1] : (ACTION) dirs[0];
                std::cout << "decided for one of the other dirs" << std::endl;
            }
        }
            break;
        default:
            break;
    }

    if (currentState.FoodInDir != -1 && (currentState.FoodInDir + 2) % 4 != currentState.lastAction)
        decision = (ACTION) currentState.FoodInDir;
    if (currentState.BaseInDir != -1 && (currentState.BaseInDir + 2) % 4 != currentState.lastAction)
        decision = (ACTION) currentState.BaseInDir;
    if (currentState.isFood && currentState.searchingHome && currentState.antFood >= MAX_FOOD_ANT_CARRYING - 2)
        decision = CHANGE_DIR;

    std::cout << "final decision: " << decision << std::endl;

    return decision;
}


// actually doing @param what with the @param ant
void ai::DO(ACTION what, Ant* ant) {
	// TODO: do what the action says
    std::cout << "doing: " << what << " for ant: " << ant->getID() << std::endl;
	switch (what) {
        case MOVE_UP:
        case MOVE_RIGHT:
        case MOVE_DOWN:
        case MOVE_LEFT:
            ant->move(what);
            break;
        case TAKE_FOOD:
            ant->addFood((unsigned int) ant->getCurrent()->getFood(ant));
            break;
        case GIVE_FOOD:
            ant->getCurrent()->getBase()->addFood(ant->getFood() - 11);
			ant->remFood(ant->getFood() - 11);
            // TODO: method ant-sided - necessary?
            break;
        case CHANGE_DIR:
            what = (ACTION) ( (ant->getDir() + 2) % 4);
            ant->move(what);
            break;
        case STAY:
            break;
    }
	ant->setLastAction(what);
}
