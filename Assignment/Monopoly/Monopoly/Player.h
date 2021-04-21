#pragma once
#include "Block.h"
#include <vector>
#include <memory>
//Razan Alsaddi
class Player
{
private:
		string playerName;
		int money;
		vector<Block*> ownedBlocks;

public :
	void setPlayerName(string playname) { playerName = playname; }
	void addMoney(int add) { money += add; }
	void subMoney(int sub) { money -= sub; }
	Player(string name) { money = 1000; playerName = name; }
	void addCily(Block* b) { ownedBlocks.push_back(b); }

	string getName() { return playerName; }
	int getMoney() { return money; }

	 void printPlayerInfo()
	 {
		 cout << "Player Info ........" << endl;
		 cout << "Player Money : "<<money<<endl;
		 for (int i = 0; i < ownedBlocks.size(); i++)
		 {
			 cout << ownedBlocks[i]->getCityName() << "   "<<endl;

		 }
	 
		 cout << "**********************"<<endl;

	 }

	
};
