#pragma once
#include <iostream>
#include <string>
using namespace std;

class Player
{
private:
	string playerName;
	float health;
	int score;

public:
	//constructor: takes in one argument to initialize player
	Player(string pname) { playerName = pname; health = 100; score = 0; }
	//destructor
	~Player() { }

	string getPlayerName() { return playerName; }
	int getScore() { return score; }
	float getHealth() { return health; }
	//add to the score
	void AddToScore(int s) { score += s; }
	//reduce health by h amount
	void ReduceHealth(float h) { health -= h; }

	void Reset() { health = 100; score = 0; }

	void PrintPlayerProperties()
	{
		cout << playerName << "'s Score is "
			<< score
			<< ". Health is: "
			<< health << endl;

	}

};