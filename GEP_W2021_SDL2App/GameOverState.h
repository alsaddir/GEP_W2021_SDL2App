#pragma once
#include "ScreenState.h"
#include<vector>
#include "Button.h"
using namespace std;

class GameOverState : public ScreenState
{
private:
	vector <Button*> m_vButtons;
	enum btn {  exit };

public:
	virtual void Update();
	virtual void Render();
	virtual void Enter();
	virtual void Exit();
	virtual void Resume() {}

};
