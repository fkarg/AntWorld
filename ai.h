#ifndef AI_H
#define AI_H


#include <ctime>


class Ant;


enum ACTION {
	MOVE_UP, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT,
	TAKE_FOOD, GIVE_FOOD, CHANGE_DIR, STAY
};



struct Surrounding_state {
	bool walls[4] = { false }; // if there's a wall in dir
    int scentThere[3] = { -1, -1, -1 }; // the scent on the current tile (for deciding with several)
    bool teamScentThere[3] = { false }; // if the scent on the tile is from the own team
	int scents[4] = { -1, -1, -1, -1 }; // how much scent there's in dir
    int scents2[4] = { -1, -1, -1, -1 }; // how much scent is there in dir(2)
	bool teamScent[4] = { false }; // if the scent is from the own team or not
    bool teamScent2[4] = { false }; // if the scent2 is from the own team or not
    int TeamScentCount = 0, TeamScent2Count = 0;
	bool isBase = false, isOwnBase = false, isFood = false; // if there's a BASE or RES on this tile, and if it is a BASE, if it's not the own
	int BaseInDir = -1, FoodInDir = -1;
	bool searchingHome = false, searchingFood = false; // if searching for food or for the base currently
	int foodThere = 0, antFood = 0, lastAction = 6;
	void print() const;       // printing debug-info
};


class ai {
private:
	//		(major, minor, test)
	// the version of the ai: 0.0.8

public:
	ai();     // initiating the pseudo-random-number generator
    void senseAndAct(Ant* itself);  // sensing, reacting and moving altogether
	Surrounding_state sense(Ant* ant);  // @returns the surrounding state around the @param ant
	ACTION decide(const Surrounding_state& currentState);  // @returns decision what to do based on the @param surrounding conditions
	void DO(ACTION what, Ant* ant);  // actually doing @param what with the @param ant
};


#endif

