#pragma once
#include"Player.h"
#include "Random.h"

class PlayerPoolGenerator
{
private:
	int playerPoolNumber;
	Player* poolGenerated;
	int skillRating;
	int purchasePrice;
public:

	
	    PlayerPoolGenerator(int num) {
		playerPoolNumber = num;
		poolGenerated = new Player[playerPoolNumber];
	}

	~PlayerPoolGenerator() { delete[] poolGenerated; poolGenerated = nullptr; }

	string RandomNameGenerator()
	{
		string razan = "razan";
		for (int i = 0; i < 5; i++)
		{
			if (i == 1)
				razan[i] = '.';
			else
				razan[i] = 'A' + GEP::RandomRange(0, 25);
			

		}
		
		return razan;
	}
	Player* GenerateThePool()
	{
		for (int i = 0; i < playerPoolNumber; i++)
		{

			 skillRating = GEP::RandomRange(20, 100);
			 purchasePrice = (GEP::RandomRange(100, 200) + 500) * skillRating;
			string name = RandomNameGenerator();
			poolGenerated[i].setSkillRating(skillRating);
			poolGenerated[i].setPurchasePrice(purchasePrice);
			poolGenerated[i].setPlayerName(name);

		}
		return poolGenerated;
	}


};

