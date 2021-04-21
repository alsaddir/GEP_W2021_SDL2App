#pragma once
#include "ScreenState.h"
#include "Button.h"
#include <vector>
#include<iostream>
using namespace std;
class MainMenueState : public ScreenState
{
	vector <Button*> m_vButtons;
	enum btn {play,exit};

public:
	MainMenueState() {}

	 void Enter();
	 void Exit();
	 void Update(); // A 'pure virtual' method.
	 void Render();
	 void Resume() {}
};

