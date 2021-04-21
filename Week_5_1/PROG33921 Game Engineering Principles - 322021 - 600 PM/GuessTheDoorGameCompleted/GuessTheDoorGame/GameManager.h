#pragma once
#include "Door.h"
#include "Random.h"
#include "Player.h"

class GameManager
{
private:
	Door * doors; //dynamically allocated array of doors
	int totalDoors; //how many doors in the game?
	int openedDoors; //how many doors opened?

	Player *player; 

	bool isGameOver;
public:
	GameManager(int totalDoorsToGenerate)
	{
		totalDoors = totalDoorsToGenerate;
		openedDoors = 0;

		doors = new Door[totalDoors]; //allocate memory 
		for (int i = 0; i < totalDoorsToGenerate; i++)
		{
			DOOR_TYPE dt = (DOOR_TYPE)GEP::RandomRange(0, 1);
			int randVal = 0;
			if (dt == 0)
				randVal = GEP::RandomRange(20, 60);
			else
				randVal = GEP::RandomRange(10, 30);

			doors[i].InitializeDoor(dt, randVal);
		}
	}

	~GameManager()
	{
		delete[] doors;
	}

	void PrintAllDoors()
	{
		for (int i = 0; i < totalDoors; i++)
		{
			doors[i].Print();
		}
	}

	int getOpenedDoorsCount() { return openedDoors; }
	int getTotalDoorsCount() { return totalDoors; }
	int getRemainingDoorsCount() { return totalDoors - openedDoors; }


	//doorNum ranges from 1 to MAX DOORS
	Door OpenDoor(int doorNum)
	{
		//doorNum-1 because the doorNum starts from 1

		doors[doorNum - 1].SetToOpen();
		return doors[doorNum - 1];

	}

	void Start()
	{
		string playerName;
		cout << "The Hidden Door Game | Single Player |\n";
	//	cout << " The goal of this game is to open doors one by one to reveal what's behind it. \n";
		cout << "Enter your name: ";
		cin >> playerName;
		//create a player object using the player name. 
		//Note that the Player's only constructor requires the player name.
		player = new Player(playerName);

	}



	void GameLoop()
	{
		int doorNumToOpen = 0;

		while (!isGameOver)
		{
			//print how many doors are left to be opened..
			cout << " Total doors: " << totalDoors << " | Remaining: " << getRemainingDoorsCount() << endl;

			cout << "Enter the door you'd like to open (1 to "<<totalDoors <<")  : " << endl;
			cin >> doorNumToOpen;

			//If doorNumToOpen has already been opened, then user has to re-enter a valid door
			if (doors[doorNumToOpen - 1].IsOpened())
			{
				cout << " That door has already been opened. Choose another door.\n";
			    continue;
			}

			//open door
			doors[doorNumToOpen - 1].SetToOpen();
			//show what was behind the door
			doors[doorNumToOpen - 1].RevealDoor();
			openedDoors += 1;
			//update player's variables
			
			if (doors[doorNumToOpen - 1].GetDoorType() == SCORE)
				player->AddToScore(doors[doorNumToOpen - 1].GetDoorValue());
			else if (doors[doorNumToOpen - 1].GetDoorType() == ENEMY)
				player->ReduceHealth(doors[doorNumToOpen - 1].GetDoorValue());

			//print updated player variables
			//print the updated score & the updated health
			player->PrintPlayerProperties();

		    //check for game end conditions

			//check for WIN condition
			//i.e. whether all doors have been opened 
			if (openedDoors == totalDoors)
			{
				isGameOver = true;
				cout << "Game Over. " 
					<< player->getPlayerName() 
					<< " wins the game.\n"
					<<"Final Score: "
					<<player->getScore()<<endl;
				
			}
			else if (player->getHealth() <= 0)
			{
				isGameOver = true;
				cout << "Game Over. "
					<< player->getPlayerName()
					<< " lost the game.\n"
					<< "Final Score: "
					<< player->getScore() << endl;
			}

			//

	    }

	}

};
