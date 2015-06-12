#include "ai.h"
#include "ant.h"


// sensing, reacting and moving
void ai::senseAndAct(Ant* itself) {
	DO(decide(sense(itself) ), itself);
}


// @returns the surrounding conditions around the @param ant
Surrounding_state ai::sense(Ant* ant) {
	Surrounding_state current;
	for (int dir = 0; dir < 4; dir++ ) {
		current.walls[dir] = ant->getCurrent()->isWall(dir);
		current.scents[dir] = ant->getCurrent()->getTeamScent(ant);
	}
	current.isBase = ant->getCurrent()->isBASE();
	current.isFood = ant->getCurrent()->isFood() > 0;
	if (current.isFood)
		current.food_there = ant->getCurrent()->isFood();
    current.ant_food = ant->getFood();

	return current;
}

// @returns the decision based on the @param state of the surroundings
ACTION ai::decide(Surrounding_state currentState) {
	ACTION decision = STAY;

	int highest = 0, dirTo = -1, possDirs = 0;

	for (int dir = 0; dir < 4; dir++) {
		if (currentState.scents[dir] > highest)
			highest = currentState.scents[dir], dirTo = dir;
		if (!currentState.walls[dir] )
			possDirs++;
	}

	if (possDirs >= 1)
		while (decision == STAY) {
			int dir = rand() % 4;
			if (!currentState.walls[dir])
				decision = (ACTION) dir;
		}
	else if (dirTo >= 0) decision = (ACTION) dirTo;

	if (currentState.isFood && currentState.food_there > 0)
		decision = TAKE_FOOD;

	if (currentState.isBase)
		if (currentState.ant_food < 10)
			decision = TAKE_FOOD;
		else if (currentState.ant_food > 10)
			decision = GIVE_FOOD;

	return decision;
}


// actually doing @param what with the @param ant
void ai::DO(ACTION what, Ant* ant) {
	// TODO: do what the action says
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
            break;
        case STAY:
            break;
    }
}
