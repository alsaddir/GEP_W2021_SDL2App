#pragma once
#include "Player.h"
#include "Asteroid.h"
#include "LifePickUp.h"
#include "SDL_mixer.h"
#include "PauseMenuPopupState.h"
#include "ScreenState.h"

#include <iostream>
using namespace std;

class GameState : public ScreenState
{
	//friend class PauseMenuPopupState ;
private:
	SDL_Texture* mainSpriteTex;//load and store the main sprite texture
	SDL_Texture*lifeSpriteTex;//load and store the main sprite texture
	SDL_Texture* bgSpriteTex; //load and store background sprite tex
	SDL_Texture* doubleScoreSpriteTex; //load and store background sprite tex
	
	SpriteEx* bg;

	Player* player;
	bool cIsPressed = false;
	vector<Asteroid*> asteroids;
	vector<LifePickUp*> lifes;
	LifePickUp* doubleScores;


	Mix_Chunk* fireSound;
	Mix_Chunk* engineSound;
	Mix_Chunk* coinSound;
	Mix_Chunk* heartSound;
	float lives = 50;
	int score = 0;
	int score_added = 5;
	
	

public:
	GameState() {}
	void Update();
	void Render();
	void Enter();
	void Exit();
	void Resume() { cout << "Resuming Game..." << endl; }
	bool CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2)
	{
		return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (r1 + r2));

	}

	void CheckCollision();
	int GetScore() { return score; }
};
