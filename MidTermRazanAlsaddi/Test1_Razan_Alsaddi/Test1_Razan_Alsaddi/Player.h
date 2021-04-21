#pragma once
#include<string.h>
#include <iostream>
using namespace std;
class Player
{
private:
	string playerName;
	int skillRating;
	double purchasePrice;

public:
	void setPlayerName(string name) { playerName = name; }
	void setSkillRating(int rate) { skillRating = rate; }
	void setPurchasePrice(double price) { purchasePrice = price; }

	//getters
	string getPlayerName() { return playerName; }
	int getSkillRating() { return skillRating; }
	double getPurchasePrice() { return purchasePrice; }

	void PrintPlayer()
	{
		cout << "name :" + playerName;
		cout << "\n";
		cout << "Skill Rating is : "<<skillRating <<"\n";
		cout << "Purchase Price is : "<<purchasePrice<<"\n";
		cout << " -------------------------\n";
	}
	

};
