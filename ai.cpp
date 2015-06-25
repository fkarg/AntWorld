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


// sensing, reacting and moving
void ai::senseAndAct(Ant* itself) {
	std::cout << "Ant " << itself->getID() << " is doing sth" << std::endl;
	DO(decide(sense(itself) ), itself);
}


// @returns the surrounding conditions around the @param ant
Surrounding_state ai::sense(Ant* ant) {
	Surrounding_state current;
	// testing the surroundings for walls and scents
	for (int dir = 0; dir < 4; dir++ ) {
		current.walls[dir] = ant->getCurrent()->isWall(dir);
		if (!current.walls[dir]) {
			current.scents[dir] = ant->getCurrent()->getTeamScent(ant) > 0 ? ant->getCurrent()->getTeamScent(ant) : ant->getCurrent()->getScent();
			current.teamScent[dir] = ant->getCurrent()->getTeamScent(ant) > 0;
		}
	}
	// what type the current tile is (except for hasAnt, since that has to be true)
	current.isBase = ant->getCurrent()->isBASE();
	current.isFood = ant->getCurrent()->isFood() > 0;
	if (current.isFood)
		current.foodThere = ant->getCurrent()->isFood();
	current.antFood = ant->getFood();
	current.lastAction = ant->getLastAction();

	// based on the food-state searching for either the base, some food, or
	if (ant->getFood() > 15 || ant->getFood() <= 5)
		current.searchingHome = true;
	else if (ant->getFood() < 15)
		current.searchingFood = true;

	return current;
}


// the @return Action what to do based on the @param currentState
ACTION ai::decide(const Surrounding_state& currentState) {

	if (currentState.foodThere >= 1
			&& currentState.antFood <= MAX_FOOD_ANT_CARRYING - 2
			&& !currentState.isBase)
		return TAKE_FOOD;
	if (currentState.isBase && currentState.antFood > 10)
		return GIVE_FOOD;
	if (currentState.isBase && currentState.antFood < 10)
		return TAKE_FOOD;

	ACTION decision = STAY;

	currentState.print();		// printing the currentState

	int highest = 0, dirTo = -1, possDir = 0, lastDir = -1;

	// testing for the number of directions without walls and the direction with the highest scent
	for (int dir = 0; dir < 4; dir++) {
		if (currentState.scents[dir] > highest)
			highest = currentState.scents[dir], dirTo = dir;
		if (!currentState.walls[dir] )
			possDir++, lastDir = dir;
	}

	// testing if this is a dead end (and if there isn't food or sth keeping the ant here too, go away from it
	if (possDir == 1 && (lastDir + 2) % 4 != currentState.lastAction)
		decision = (ACTION) lastDir;

	// if there's only two directions possible, you came from one and will go to the other
	// special cases: you are on the BASE or a RES, and either left or are taking food TODO
	if (possDir == 2)
		if ( (lastDir + 2) % 4 != currentState.lastAction)
			decision = (ACTION) lastDir;
		else while (decision == STAY) {
			int newDir = rand() % 4;
			if ( (newDir + 2) % 4 != currentState.lastAction
					&& !currentState.walls[newDir] )
				decision = (ACTION) newDir;
		}

	// if there's more than two possibilities, a random event is being chosen for the time being
	if (possDir >= 3)
		while (decision == STAY) {
			int newDir = rand() % 4;
			if ( (newDir + 2) % 4 != currentState.lastAction
					&& !currentState.walls[newDir] )
				decision = (ACTION) newDir;
		}

	// TODO: following scent or !follow it after the conditions

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
        case STAY:
            break;
    }
	ant->setLastAction(what);
}
