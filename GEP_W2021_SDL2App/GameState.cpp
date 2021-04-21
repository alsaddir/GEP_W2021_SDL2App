#include"GameState.h"
#include"GameEngine.h"
#include <ctime>
#include "PauseMenuPopupState.h"
#include "GameOverState.h"




void GameState::Render()
{
	SDL_RenderClear(GameEngine::Instance()->GetRenderer()); //clear previously drawn frame

	bg->Render();
	if (player) player->Render();
	if (doubleScores) doubleScores->Render();
	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->Render();
	}

	for (int i = 0; i < lifes.size(); i++)
	{
		lifes[i]->Render();
	}
	string s = "Score : " + to_string(score) + "&& Lives :"+to_string(lives);
	RenderFont(s.c_str(), 32, 50, true);
	ScreenState::Render();
}

void GameState::Enter()
{
	//
	bgSpriteTex = GameEngine::Instance()->LoadTexture("Assets/Sprites/background.png");
	mainSpriteTex = GameEngine::Instance()->LoadTexture("Assets/Sprites/Sprites.png");
	doubleScoreSpriteTex= GameEngine::Instance()->LoadTexture("Assets/Sprites/Heart.png");
	lifeSpriteTex = GameEngine::Instance()->LoadTexture("Assets/Sprites/life.png");
	//lifeSpriteTex = GameEngine::Instance()->LoadTexture("Assets/Sprites/Sprites.png");


	SDL_Rect bgSrcRect = { 0,0,0,0 };
	//load the sound
	fireSound = Mix_LoadWAV("Assets/Aud/Fire.wav");
	engineSound = Mix_LoadWAV("Assets/Aud/Engines.wav");
	coinSound = Mix_LoadWAV("Assets/Aud/coin.wav");
	heartSound = Mix_LoadWAV("Assets/Aud/heart.wav");

	//load the font
	m_pFont = TTF_OpenFont("Assets/Fonts/LTYPE.TTF", 30);//30 is the initial font size

	//to set the volum of each chunk
	Mix_VolumeChunk(fireSound, 70);
	Mix_VolumeChunk(engineSound, 50);
	Mix_VolumeChunk(coinSound, 70);
	Mix_VolumeChunk(heartSound, 70);

	//to give us width/heigh ogf the texture
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect = { 0,0,0,0 };
	// we get the window dimension using SDL_GetWindowSize()
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);

	srand(time(0));

	/* *************** Astroids ***************** */
	SDL_Rect asteroidSrcRect = { 124,0,66,66 };// 64x64 is the width/high of asteroid
	SDL_Rect asteroidDesRect = { 0,0,64,64 };// 64x64 is the width/high of asteroid



	//generate astroides , for now we want 5
	for (int i = 0; i < 5; i++)
	{
		//generated random speed 
		float r = (1 - rand() % 2 * 2) * (rand() % 6 + 1);

		asteroidDesRect.x = (rand() % 700) + 1; // genetare between 1 & 700 pixels
		asteroidDesRect.y = (rand() % 500) + 1; // generate between 1 and 600 pixel
		float r2 = (rand() % 63) + 30;
		asteroidDesRect.h = r2;
		asteroidDesRect.w = r2;

		Asteroid* ast = new Asteroid(mainSpriteTex, asteroidSrcRect, asteroidDesRect, r);
		asteroids.push_back(ast);//push it into the vector


	}

	SDL_Rect lifesSrcRect = { 0,0,64,64 };// 64x64 is the width/high of asteroid
	SDL_Rect lifesDesRect = { 0,0,75,75 };// 64x64 is the width/high of asteroid

	//SDL_Rect lifesSrcRect = { 0,0,64,64 };// 64x64 is the width/high of asteroid
	////SDL_QueryTexture(lifeSpriteTex, NULL, NULL, &lifesSrcRect.w, &lifesSrcRect.h);
	//SDL_Rect lifesDesRect = { 0,0,64,64 };// 64x64 is the width/high of asteroid

	for (int j = 0; j < 3; j++)
	{
		//generated random speed 
		float r = (1 - rand() % 2 * 2) * (rand() % 6 + 1);

		lifesDesRect.x = (rand() % 700) + 1; // genetare between 1 & 700 pixels
		lifesDesRect.y = (rand() % 500) + 1; // generate between 1 and 600 pixel
		lifesDesRect.h = 64;
		lifesDesRect.w = 64;

		LifePickUp* life = new LifePickUp(lifeSpriteTex, lifesSrcRect, lifesDesRect, r);
		lifes.push_back(life);//push it into the vector


	}


	SDL_Rect dScoreSrcRect = { 0,0,32,32};// 64x64 is the width/high of asteroid
	SDL_Rect dScoreDesRect = { 0,0,100,100 };// 64x64 is the width/high of asteroid
	float rotate = (1 - rand() % 2 * 2) * (rand() % 6 + 1);
	dScoreDesRect.x = (rand() % 700) + 1; // genetare between 1 & 700 pixels
	dScoreDesRect.y = (rand() % 500) + 1; // generate between 1 and 600 pixel
	doubleScores= new LifePickUp(doubleScoreSpriteTex, dScoreSrcRect, dScoreDesRect, rotate);




	player = new Player(mainSpriteTex, bgDestRect.w * 0.5, bgDestRect.h - 100);

}

void GameState::CheckCollision()
{
	//check for the player and asteroid collision
	for (int i = 0; i < (int)asteroids.size(); i++)
	{
		if (CircleCollisionTest(player->GetX(), player->GetY(),
			asteroids[i]->GetX(), asteroids[i]->GetY(),
			player->GetRadius(), asteroids[i]->GetRadius()
		))
		{

			//there was a player-asteroid collision!!!
			cout << "Player collided with an asteroid and got killed!!\n";
			//we can delete the player...
			lives -= 1;
			
			if (lives == 0)
			{
				delete player;
				player = nullptr;
				//isRunning = false;
				return;
			}
		}

	}

//collesion check for the lifes pick up
	for (int i = 0; i < (int)lifes.size(); i++)
	{
		if (CircleCollisionTest(player->GetX(), player->GetY(),
			lifes[i]->GetX(), lifes[i]->GetY(),
			player->GetRadius(), lifes[i]->GetRadius()
		))
		{

			//there was a player-asteroid collision!!!
			cout << "Player collided with an asteroid and got killed!!\n";
			//we can delete the player...
			Mix_PlayChannel(-1, coinSound, 0);
			lives += 1;
			delete lifes[i];
			lifes[i] = nullptr;
			lifes.erase(lifes.begin() + i);
		}

	}


	//Pick up the heart which  double the score
	if (doubleScores) {
		if (CircleCollisionTest(player->GetX(), player->GetY(),
			doubleScores->GetX(), doubleScores->GetY(),
			player->GetRadius(), doubleScores->GetRadius()
		))
		{

			//there was a player-asteroid collision!!!
			cout << "Player collided with an asteroid and got killed!!\n";
			//we can delete the player...
			Mix_PlayChannel(-1, heartSound, 0);
			score_added *= 2;
			delete doubleScores;
			doubleScores = nullptr;
		}

	}






	bool isBreakOutOfLoop = false;
	//check for bullet and asteroid collision
	for (int b = 0; b < (int)player->GetBullets().size(); b++)
	{

		for (int i = 0; i < (int)asteroids.size(); i++)
		{

			Bullet* bullet = player->GetBullets()[b];

			if (CircleCollisionTest(bullet->GetX(), bullet->GetY(),
				asteroids[i]->GetX(), asteroids[i]->GetY(),
				bullet->GetRadius(), asteroids[i]->GetRadius()
			))
			{

				cout << "Bullet collided with an asteroid!!\n";
				//may be, add to score here... 
				score += score_added;
				//cleanup/destroy the bullet
				delete bullet;
				player->GetBullets()[b] = nullptr;
				player->GetBullets().erase(player->GetBullets().begin() + b);

				//destroy the asteroid
				if ((asteroids[i]->GetWidth() - 20 ) > 0) 
				{
					asteroids[i]->SetHightAndWidth(20);
				}
				else {
					delete asteroids[i];
					asteroids[i] = nullptr;
					asteroids.erase(asteroids.begin() + i);
				}

				isBreakOutOfLoop = true;

			}
			if (isBreakOutOfLoop)	break;
		}

		if (isBreakOutOfLoop)	break;
	}

	if (isBreakOutOfLoop)
	{
		player->GetBullets().shrink_to_fit();
		asteroids.shrink_to_fit();
	}

}

void GameState::Update()
{
	
	
	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_ESCAPE) == 1)
	{
		GameEngine::Instance()->GetFSM()->PushState(new PauseMenuPopupState());
		return; //to make sure we don't run the game in background while pause menu shows
	}

	if (lives == 0 || asteroids.size() == 0)
	{
		GameEngine::Instance()->GetFSM()->PushState(new GameOverState());
		return; //to make sure we don't run the game in background while pause menu shows
	}

	if (player) player->Update();

	for (int i = 0; i < asteroids.size(); i++)
		asteroids[i]->Update();

	for (int i = 0; i < lifes.size(); i++)
		lifes[i]->Update();


	if (player) this->CheckCollision();

	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_SPACE) && player)
	{
		//to do:: launch a missile...
		Mix_PlayChannel(-1, fireSound, 0); //-1 means we ask the mixer to play on the first available channel. the third argument: 0, means we play it just once (no looping)
		player->SpawnBullet();
	}
	//Play engine sound....
	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_W))
	{
		if (!Mix_Playing(15)) //if channel 15 is not playing
			Mix_PlayChannel(15, engineSound, -1);   //-1 because we want to loop the sound...

	}
	if (GameEngine::Instance()->KeyUp(SDL_SCANCODE_W))
	{
		if (player)
		{
			Mix_FadeOutChannel(15, 250); //250 is in milliseconds.. the time over which the audio will fade out...
			player->SetIdle();

		}

	}

	SDL_Delay(10);


}




void GameState::Exit() {}

