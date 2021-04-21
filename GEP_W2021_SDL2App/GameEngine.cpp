#include "GameEngine.h"
#include <cstdlib>
#include <ctime>
#include "MainMenueState.h"


GameEngine* GameEngine::Instance()
{
	static GameEngine* instance;
	if (instance == nullptr)
		instance = new GameEngine();

	return instance;
}

bool GameEngine::InitGameEngine()
{
	window = SDL_CreateWindow("First SDL App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (!window)
	{
		cout << "Window initialization failed.\n";
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		cout << "Renderer initialization failed.\n";
		return false;
	}

	//check if TTF engine can be used.... if it can't be initialized, return false
	if (TTF_Init() != 0)
	{
		cout << "TTF Font init failed.\n";
		return false;
	}

	if (Mix_Init(MIX_INIT_MP3) == 0)
	{
		cout << "Mixer init faild";
	}
	else
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
		Mix_AllocateChannels(16);
	}

	m_iKeystates = SDL_GetKeyboardState(nullptr);
	m_pFSM = new StateMachine();
	m_pFSM->ChangeState(new MainMenueState());
	return true;
}




SDL_Texture* GameEngine::LoadTexture(const char* path)
{
	SDL_Surface* surface = IMG_Load(path);
	return SDL_CreateTextureFromSurface(renderer, surface);
}




/*
void GameEngine::Render()
{
	SDL_RenderClear(renderer); //clear previously drawn frame

	bg->Render();
	if (player) player->Render();
	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->Render();
	}
	string s = "Score" + to_string(score);
	RenderFont(s.c_str(),32,50,true);
	SDL_RenderPresent(renderer); //must call this to render the above defined
}

*/

void GameEngine::Render()
{
	GetFSM()->Render();
}

void GameEngine::Quit()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	//shutdown SDL
	SDL_Quit();

	//TTF_CloseFont(m_pFont);
	TTF_Quit();

}

bool GameEngine::KeyDown(SDL_Scancode c)
{
	if (m_iKeystates == nullptr)
		return false;

	if (m_iKeystates[c] == 1)
		return true;
	else return false;
}

bool GameEngine::KeyUp(SDL_Scancode c)
{
	if (m_iKeystates == nullptr)
		return false;

	if (m_iKeystates[c] == 0)
		return true;
	else return false;
}


void GameEngine::Input()
{

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEMOTION) //if mouse movement is detected
		{
			SDL_GetMouseState(&m_iMouseX, &m_iMouseY);
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) //if mouse movement is detected
		{
			if (event.button.button == SDL_BUTTON_LEFT)
				m_bLeftMouse = true;
		}
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
				m_bLeftMouse = false;

			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}

			////check if key was pressed
			//if (event.type == SDL_KEYDOWN)
			//{
			//	switch (event.key.keysym.sym)
			//	{
			//	case SDLK_ESCAPE:
			//		isRunning = false;
			//		break;

			//	}

			//}
		}
	}
}


/*void GameEngine::Update()
{
	if(player)player->Update(cIsPressed);
	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->Update();
	}
	if (player) this->CheckCollision();
	//slow down by using SDL_Delay
	SDL_Delay(10); //pause the game loop for 10 milliseconds to slow down the game to a decent speed

}*/


void GameEngine::Update()
{
	GetFSM()->Update();
}
