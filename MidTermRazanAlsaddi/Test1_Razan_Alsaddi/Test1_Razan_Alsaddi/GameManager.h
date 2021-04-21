#pragma once
#include"Team.h"
class GameManager
{

private:
	Team* team;
	PlayerPoolGenerator* pool;
	Player* playersGenerated;
	int poolNum;
	int purchesdTeam;
	string teamName;

public:
	~GameManager()
     {
		delete team;
		delete pool;
		team = nullptr;
		pool = nullptr;
	}
	void Start()
	{
		 teamName;
    	cout << "Please enter your team name \n";
		cin >> teamName;
		team = new Team(teamName);
		cout << "Please enter pool players generated num \n";
		cin >> poolNum;
		pool= new PlayerPoolGenerator(poolNum);
		playersGenerated = pool->GenerateThePool();
	}



	void GameLoop()
	{
		int purchse;
		for (int i = 0; i < poolNum; i++)
		{
			if (team->getCashAvailble() < playersGenerated[i].getPurchasePrice() && i==(poolNum-1))
			{
				cout << "Sorry no more cash availbel to buy the player they left \n";
				cout << "********************* \n";
				break;
			}
			else if (team->getCashAvailble() < playersGenerated[i].getPurchasePrice() && i < poolNum)
			{
				continue;
			}
			cout << "********************* \n";
            cout << "Card# "<<i+1<<"/"<<poolNum<<"\n";
			cout << "********************* \n";
			playersGenerated[i].PrintPlayer();
			cout << "********************* \n";
			team->printInfo();
			cout << "Purchase this card? Yes (1) or No (0)?  \n";
			cin >> purchse;
			if (purchse == 0)
				continue;
			else
			{
				
				team->addPlayer(playersGenerated[i]);
				team->addSkill(playersGenerated[i].getSkillRating());
				team->subCashAvailable(playersGenerated[i].getPurchasePrice());
				cout << "--------------- \n";
				team->printInfo();
				cout << "--------------- \n";
				purchesdTeam++;
			
			}
		}
	}


	void printAll() 
	{
		cout << "********************* \n";
		cout << "Team Name "<< teamName << "\n";
		cout << "Team Member are : " << "\n";
		team->printTeam();
		cout << "********************* \n";
		team->printInfo();
		cout << "Average Skill Rating: " << team->getAve();
	}



};
