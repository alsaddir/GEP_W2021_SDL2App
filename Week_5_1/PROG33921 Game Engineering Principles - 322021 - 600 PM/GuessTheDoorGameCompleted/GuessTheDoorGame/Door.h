#pragma once
#include <iostream>
#include <string>
using namespace std;

enum DOOR_TYPE { SCORE, ENEMY};

class Door
{
private: 
	DOOR_TYPE doorType;
	int value;   //this contains either score or damage, depending on the door type
	bool isOpened=false;
public: 
	 Door() { }
	~Door() { }
	void InitializeDoor(DOOR_TYPE dt, int val) 
	{ doorType = dt;  value = val; }

	void Print() {  cout << "Door Type is: " << doorType << " | val: " << value<<endl; }

	int GetDoorValue() { return value; }
	DOOR_TYPE GetDoorType() { return doorType; }

	//Sets the door to open state
	void SetToOpen() 
	{ isOpened = true; }

	//returns true if the door has already been opened
	bool IsOpened() 
	{ return isOpened; }

	void RevealDoor()
	{
		//if score type...
		//tell the user that they earned X points
		//else if enemy type,
		//tell the user that they got hit by an enemy behind the door and show how much damage was
		//inflicted

		if (doorType == SCORE)
		{
			cout << "You earned " << value << " points!!";
		}
		else if (doorType == ENEMY)
		{
			cout << "You got hit by an enemy! Damage inflicted: " << value;
		}

	}

};