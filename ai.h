#ifndef ANTWORLD_AI_H
#define ANTWORLD_AI_H


#include <ctime>


class Ant;


enum ACTION {
	MOVE_UP, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT,
	TAKE_FOOD, GIVE_FOOD, STAY
};



struct Surrounding_state {
	bool walls[4] = { false }; // if there's a wall in dir
	int scents[4] = { -1, -1, -1, -1 }; // how much scent there's in dir
	bool isBase = false, isFood = false; // if there's a BASE or RES on this tile
	bool searchingHome = false, searchingFood = false; // if searching for food or for the base currently
	int foodThere = 0, antFood = 0, lastAction = 6;
	void print() const;       // printing debug-info
};


class ai {
private:
    float version = 1.002;

public:
	ai(){};     // FIXME: currently crashing for usual ants
	void senseAndAct(Ant* itself);  // sensing, reacting and moving altogether
	Surrounding_state sense(Ant* ant);  // @returns the surrounding state around the @param ant
	ACTION decide(const Surrounding_state& currentState);  // @returns decision what to do based on the @param surrounding conditions
	void DO(ACTION what, Ant* ant);  // actually doing @param what with the @param ant
};


#endif //ANTWORLD_AI_H

