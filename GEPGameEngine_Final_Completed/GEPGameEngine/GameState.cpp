#include "GameState.h"
#include "Game.h"
#include "PauseMenuPopupState.h"
void GameState::Enter()
{
	bgSpriteTex = Game::Instance()->LoadTexture("background.png");
	mainSpriteTex = Game::Instance()->LoadTexture("Sprites.png");

	m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 30);

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(Game::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);


	SDL_Rect asteroidSrcRect;
	asteroidSrcRect.x = 124;
	asteroidSrcRect.y = 0;
	asteroidSrcRect.w = asteroidSrcRect.h = 66;//66 pixelsx66 pixels is each cell's dimension

	SDL_Rect asteroidDestRect;
	asteroidDestRect.w = asteroidDestRect.h = 66;

	for (int i = 0; i < 5; i++)
	{
		//generate a random speed
		float r = (1 - rand() % 2 * 2) * (rand() % 6 + 1);

		asteroidDestRect.x = (rand() % 700) + 1; //generate between 1 and 700
		asteroidDestRect.y = (rand() % 600) + 1;//generate between 1 and 600

		Asteroid* ast = new Asteroid(mainSpriteTex, asteroidSrcRect, asteroidDestRect, r);
		asteroids.push_back(ast);
	}

	player = new Player(mainSpriteTex, bgDestRect.w*0.5, bgDestRect.h - 100);

	fireSound = Mix_LoadWAV("Fire.wav");
	engineSound = Mix_LoadWAV("Engines.wav");
	Mix_VolumeChunk(fireSound, 50);
	Mix_VolumeChunk(engineSound, 50);

}


void GameState::Update()
{
	if (Game::Instance()->KeyDown(SDL_SCANCODE_ESCAPE) == 1)
	{
		Game::Instance()->GetFSM()->PushState(new PauseMenuPopupState());
		return; //to make sure we don't run the game in background while pause menu shows
	}

	if (player) player->Update();

	for (int i = 0; i < asteroids.size(); i++)
		asteroids[i]->Update();

	if (player) this->CheckCollision();

	if (Game::Instance()->KeyDown(SDL_SCANCODE_SPACE) && player)
	{
		//to do:: launch a missile...
		Mix_PlayChannel(-1, fireSound, 0); //-1 means we ask the mixer to play on the first available channel. the third argument: 0, means we play it just once (no looping)
		player->SpawnBullet();
	}
	//Play engine sound....
	if (Game::Instance()->KeyDown(SDL_SCANCODE_W))
	{
		if (!Mix_Playing(15)) //if channel 15 is not playing
			Mix_PlayChannel(15, engineSound, -1);   //-1 because we want to loop the sound...

	}
	if (Game::Instance()->KeyUp(SDL_SCANCODE_W))
	{
		if (player)
		{
			Mix_FadeOutChannel(15, 250); //250 is in milliseconds.. the time over which the audio will fade out...
			player->SetIdle();

		}

	}




}


void GameState::Render()
{
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 0, 0, 255); //set background window color
	SDL_RenderClear(Game::Instance()->GetRenderer()); //clear the screen

	bg->Render();

	if (player) player->Render();

	for (int i = 0; i < asteroids.size(); i++)
		asteroids[i]->Render();

	string s = "Score: " + to_string(score);

	RenderFont(true, s.c_str(), 32, 50);

	ScreenState::Render();


}


void GameState::Exit()
{
	//to-do:: de-allocate memory, texture, surface etc, sound 

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
			delete player;
			player = nullptr;

			return;
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
				score += 5;

				//cleanup/destroy the bullet
				delete bullet;
				player->GetBullets()[b] = nullptr;
				player->GetBullets().erase(player->GetBullets().begin() + b);

				//destroy the asteroid
				delete asteroids[i];
				asteroids[i] = nullptr;
				asteroids.erase(asteroids.begin() + i);

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
