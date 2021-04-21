#include <iostream>
#include "Game.h"
#include "MainMenuState.h"

using namespace std;

//Singleton pattern for Game class 
//is defined as follows
Game* Game::Instance()
{
	static Game* instance = new Game();
	return instance;
}

bool Game::Init(const char* title, const int xPos, const int yPos, const int width, const int height,
	const int flags)
{
	//0 means success
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL Initialization successful\n";

		sdlWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (sdlWindow == nullptr)
		{
			cout << "Window initialization failed.\n";
			return false;
		}
		cout << "Window successfully created.\n";
		sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
		if (sdlRenderer == nullptr)
		{
			cout << "renderer initialization failed.\n";
			return false;
		}
	}
	else
	{
		cout << "SDL Initialization failed\n";
		return false;
	}

	if (Mix_Init(MIX_INIT_MP3) == 0) 
	{
		cout << "Mixer init failed\n";
		return false;
	}
	else
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
		Mix_AllocateChannels(16);
		fireSound = Mix_LoadWAV("Fire.wav");
		engineSound = Mix_LoadWAV("Engines.wav");
		Mix_VolumeChunk(fireSound, 50);
		Mix_VolumeChunk(engineSound, 50);
	}

	if (TTF_Init() == 0) //font init is succesful
	{
		cout << "Font init success!\n";
	}
	else
	{
		cout << "Font init fail!\n";
		return false;
	}


	m_iKeystates = SDL_GetKeyboardState(nullptr);
	isAppRunning = true;

	m_pFSM = new StateMachine();
	m_pFSM->ChangeState(new MainMenuState());

	return true;
}

void Game::InitializeGame()
{
	bgSpriteTex = LoadTexture("background.png");
	mainSpriteTex = LoadTexture("Sprites.png");

	m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 30);

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(sdlWindow, &bgDestRect.w, &bgDestRect.h);

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
}

SDL_Texture* Game::LoadTexture(const char* path)
{
	SDL_Surface *surface = IMG_Load(path);
	return SDL_CreateTextureFromSurface(sdlRenderer, surface);

}

 
bool Game::IsRunning()
{
	return isAppRunning;
}

//check whether a specific key, passed as argument 'c'
//is pressed down
bool Game::KeyDown(SDL_Scancode c)
{
	if (m_iKeystates == nullptr)
		return false;

	if (m_iKeystates[c] == 1)
		return true;
	else return false;
}

bool Game::KeyUp(SDL_Scancode c)
{
	if (m_iKeystates == nullptr)
		return false;

	if (m_iKeystates[c] == 0)
		return true;
	else return false;
}

/*
void Game::Update()
{
	if (player) player->Update();

	 	for (int i = 0; i < asteroids.size(); i++)
		asteroids[i]->Update();

		if (player) this->CheckCollision();

	if (KeyDown(SDL_SCANCODE_SPACE) && player)
	{
		//to do:: launch a missile...
		Mix_PlayChannel(-1, fireSound, 0); //-1 means we ask the mixer to play on the first available channel. the third argument: 0, means we play it just once (no looping)
		player->SpawnBullet();
	}
	//Play engine sound....
	if (KeyDown(SDL_SCANCODE_W))
	{
		if(!Mix_Playing(15)) //if channel 15 is not playing
	     	Mix_PlayChannel(15, engineSound, -1);   //-1 because we want to loop the sound...

	}
	if (KeyUp(SDL_SCANCODE_W))
	{
		if (player)
		{
			Mix_FadeOutChannel(15, 250); //250 is in milliseconds.. the time over which the audio will fade out...
			player->SetIdle();
		
		}
		
		}



}
*/

void Game::Update()
{

	GetFSM()->Update();
}


void Game::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isAppRunning = false;
			break;
	
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&m_iMouseX, &m_iMouseY);
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
				m_bLeftMouse = true;
			break;

		case SDL_MOUSEBUTTONUP:
		{
			if (event.button.button == SDL_BUTTON_LEFT)
				m_bLeftMouse = false;

			//if (event.button.button == SDL_BUTTON_LEFT && player)
			//{
			//	//do something...  such as fire a bullet/missile
			//	//and play sound
			//	Mix_PlayChannel(-1, fireSound, 0); //-1 means we ask the mixer to play on the first available channel. the third argument: 0, means we play it just once (no looping)
			//	player->SpawnBullet();
			//}
		}
		break;

		}
	}
}

/*
void Game::Render()
{
	SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255); //set background window color
	SDL_RenderClear(sdlRenderer); //clear the screen
								  //SDL_SetRender

	bg->Render();

	if (player) player->Render();

	for (int i = 0; i < asteroids.size(); i++)
		asteroids[i]->Render();

	string s = "Score: " + to_string(score);

	RenderFont(true,s.c_str(), 32, 50);

	SDL_RenderPresent(sdlRenderer); //draw the current frame

}

*/


void Game::Render()
{
	GetFSM()->Render();
}

void Game::Clean()
{
	cout << "Cleaning up and shutting down engine...\n";
	SDL_DestroyWindow(sdlWindow);
	SDL_DestroyRenderer(sdlRenderer);

	TTF_CloseFont(m_pFont);
	TTF_Quit();

	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();

	SDL_Quit();

}


void Game::CheckCollision()
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
				if(isBreakOutOfLoop)	break;
		}

		if (isBreakOutOfLoop)	break;
	}

	if (isBreakOutOfLoop)
	{
		player->GetBullets().shrink_to_fit();
		asteroids.shrink_to_fit();
	}

}


void Game::RenderFont(bool isRefreshText, const char *text, int x, int y)
{

	if (isRefreshText)
	{
		SDL_Color textColor = { 255,255,255,0 };//white color
		SDL_Surface * fontSurface = TTF_RenderText_Solid(m_pFont, text, textColor);
		
		SDL_DestroyTexture(m_pFontTexture); //need to de-allocate previous font texture
		m_pFontTexture = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), fontSurface);
		m_rFontRectScore = { x,y,fontSurface->w,fontSurface->h };

	}

	SDL_RenderCopy(Game::Instance()->GetRenderer(), m_pFontTexture, 0, &m_rFontRectScore);

}


