#include "PauseMenuPopupState.h"
#include <iostream>
#include "GameEngine.h"
#include "GameState.h"
#include "MainMenueState.h"
using namespace std;

void PauseMenuPopupState::Update()
{
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	//close the pause menu popup
	if (m_vButtons[btn::resume]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->PopState();
	}
	//else if exit was clicked we need to go back to main menu
	else if (m_vButtons[btn::exit]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->Clean();// cleare all the states , including GameState on bottom
		//Go back to manin menu
		GameEngine::Instance()->GetFSM()->ChangeState(new MainMenueState());
	}
}

void PauseMenuPopupState::Render()
{
	//GameEngine::Instance()->GetFSM()->GetStates().front()->Render();
	//SDL_SetRenderDrawBlendMode(GameEngine::Instance()->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(),64,64,128,128);

	//draw background
	SDL_Rect rect = { 256,128,450,450 };
	SDL_RenderFillRect(GameEngine::Instance()->GetRenderer(),&rect);

	//draw the buttons
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		m_vButtons[i]->Render();
		
	}

	//string s = "Score : ";
	//std::cout << "";
	//SDL_Color textColor = { 255,255,255,0 };//white color
	//m_pFont = TTF_OpenFont("Assets/Fonts/LTYPE.TTF", 30);//30 is the
	//SDL_Surface* fontSurface = TTF_RenderText_Solid(m_pFont, s.c_str(), textColor);
	//SDL_DestroyTexture(m_pFontTexture); //need to de-allocate previous font texture
	//m_pFontTexture = SDL_CreateTextureFromSurface(GameEngine::Instance()->GetRenderer(), fontSurface);
	//m_rFontRect = { 0,0,fontSurface->w,fontSurface->h };
	SDL_RenderCopy(GameEngine::Instance()->GetRenderer(), m_pFontTexture, 0, &m_rFontRect);

	GameState g;
	
	//RenderFont(s.c_str(), 0, 0, false);
	ScreenState::Render();

}

void PauseMenuPopupState::Enter()
{
	cout << "Entring Pause"<<endl;
	m_vButtons.push_back(new Button("Assets/Img/resume.png", {0,0,200,80}, {412,200,200,80}));
	m_vButtons.push_back(new Button("Assets/Img/exit.png", { 0,0,400,100 }, { 412,400,200,80 }));
}

void PauseMenuPopupState::Exit()
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
