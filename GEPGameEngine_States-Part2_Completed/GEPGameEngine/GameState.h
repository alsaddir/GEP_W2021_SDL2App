#pragma once
#include "ScreenState.h"
#include <iostream>
using namespace std;

class GameState : public ScreenState
{
private:


public:
	GameState() {}
	void Update();
	void Render();
	void Enter();
	void Exit();
	void Resume() { cout << "Resuming Game..." << endl; }
	bool CircleCollisionTest(double, double, double, double, double, double);
	void CheckCollision();
};
