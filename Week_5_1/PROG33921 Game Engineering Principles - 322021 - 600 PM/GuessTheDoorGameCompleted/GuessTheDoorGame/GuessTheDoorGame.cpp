// GuessTheDoorGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GameManager.h"

int main()
{
	GameManager *gMgr= new GameManager(5); 
	gMgr->PrintAllDoors();

	//initialize the game and show the main menu; get player's name etc
	gMgr->Start();
	//game loop is responsible for getting input from the user and running the overall game logic	
    gMgr->GameLoop();

    return 0;
}

