#include "GameOverState.h"
#include <iostream>
#include "GameEngine.h"
#include "GameState.h"
#include "MainMenueState.h"
using namespace std;

void GameOverState::Update()
{
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	
	//else if exit was clicked we need to go back to main menu
	 if (m_vButtons[btn::exit]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->Clean();// cleare all the states , including GameState on bottom
		//Go back to manin menu
		GameEngine::Instance()->GetFSM()->ChangeState(new MainMenueState());
	}
}

void GameOverState::Render()
{
	//GameEngine::Instance()->GetFSM()->GetStates().front()->Render();
	//SDL_SetRenderDrawBlendMode(GameEngine::Instance()->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 64, 64, 128, 128);

	//draw background
	SDL_Rect rect = { 256,128,450,450 };
	SDL_RenderFillRect(GameEngine::Instance()->GetRenderer(), &rect);

	//draw the buttons
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		m_vButtons[i]->Render();

	}
	GameState g;
	string s = "The Final Score is " +to_string(g.GetScore());
	m_pFont = TTF_OpenFont("Assets/Fonts/LTYPE.TTF", 30);//30 is the
	RenderFont(s.c_str(),350,50 ,false);
	SDL_RenderCopy(GameEngine::Instance()->GetRenderer(), m_pFontTexture, 0, &m_rFontRect);


	//RenderFont(s.c_str(), 0, 0, false);
	ScreenState::Render();

}

void GameOverState ::Enter()
{
	cout << "Entring Pause" << endl;
	m_vButtons.push_back(new Button("Assets/Img/exit.png", { 0,0,400,100 }, { 412,400,200,80 }));
}

void GameOverState::Exit()
{
	cout << "Exiting Pause ... " << endl;
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();

}
