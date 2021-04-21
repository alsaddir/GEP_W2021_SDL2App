#pragma once
#include "Random.h"
//Razan Alsaddi


// Create a Dice class that can be initialized with any number of sides.
//Implement a Roll function that will randomly return a dice side.
class Dice
{
public:
	int roll()
	{ 
		return GEP::RandomRange(1, 6);
	}
};
