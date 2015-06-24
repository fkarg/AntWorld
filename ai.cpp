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
	for (int dir = 0; dir < 4; dir++ ) {
		current.walls[dir] = ant->getCurrent()->isWall(dir);
		if (!current.walls[dir])
			current.scents[dir] = ant->getCurrent()->getTeamScent(ant);
	}
	current.isBase = ant->getCurrent()->isBASE();
	current.isFood = ant->getCurrent()->isFood() > 0;
	if (current.isFood)
		current.foodThere = ant->getCurrent()->isFood();
    current.antFood = ant->getFood();
    current.lastAction = ant->getLastAction();

	if (ant->getFood() > 15 || ant->getFood() <= 5)
		current.searchingHome = true;
	else if (ant->getFood() < 15)
		current.searchingFood = true;

	return current;
}


/*
// @returns the decision based on the @param state of the surroundings
ACTION ai::decide(Surrounding_state currentState) {

    currentState.print();

	ACTION decision = STAY;

	int highest = 0, dirTo = -1, possDirs = 0;

	for (int dir = 0; dir < 4 && (dir + 2) % 4 != currentState.lastAction; dir++) {
		if (currentState.scents[dir] > highest)
			highest = currentState.scents[dir], dirTo = dir;
		if (!currentState.walls[dir] )
			possDirs++;
	}bg

	if (possDirs >= 1)
		while (decision == STAY) {
			int dir = rand() % 4;
			if (!currentState.walls[dir] && (dir + 2) % 4 != currentState.lastAction)
				decision = (ACTION) dir;
		}
	else if (dirTo >= 0 && (dirTo + 2 % 4) != currentState.lastAction) decision = (ACTION) dirTo;

	if (currentState.isFood && currentState.foodThere > 0
            && currentState.antFood < MAX_FOOD_ANT_CARRYING - 2)
		decision = TAKE_FOOD;

	if (currentState.isBase)
		if (currentState.antFood < 10)
			decision = TAKE_FOOD;
		else if (currentState.antFood > 10)
			decision = GIVE_FOOD;

	return decision;
}
*/


ACTION ai::decide(const Surrounding_state &currentState) {
	currentState.print();

	return STAY
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
            // ant->getCurrent()->getBase()->addFood(ant->getFood())
            // TODO: method ant-sided
            break;
        case STAY:
            break;
    }
	ant->setLastAction(what);
}
