#ifndef ANTWORLD_AI_H
#define ANTWORLD_AI_H


#include <ctime>


class Ant;


enum ACTION {
    MOVE_UP, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT,
    TAKE_FOOD, GIVE_FOOD, STAY
};



struct Surrounding_state {
	bool walls[4] = { false };
	int scents[4] = { -1, -1, -1, -1 };
	bool isBase = false, isFood = false;
	int food_there = 0, ant_food;
};


class ai {
private:
    float version = 1.002;

public:
	ai(){};     // FIXME: currently crashing
	void senseAndAct(Ant* itself);  // sensing, reacting and moving altogether
	Surrounding_state sense(Ant* ant);  // @returns the surrounding state around the @param ant
	ACTION decide(Surrounding_state currentState);  // @returns decision what to do based on the @param surrounding conditions
	void DO(ACTION what, Ant* ant);  // actually doing @param what with the @param ant
};


#endif //ANTWORLD_AI_H
