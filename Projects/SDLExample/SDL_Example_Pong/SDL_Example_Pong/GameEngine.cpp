#include "GameEngine.h"



GameEngine* GameEngine:: Instance()
{
	static GameEngine* instance;
	if (instance == nullptr)
		instance = new GameEngine();
	return instance;
}


bool GameEngine :: InitGameEngine()
{
	window = SDL_CreateWindow("First SDL App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH, WINDOW_HEIGHT, 0);
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

	return true;
}


void GameEngine :: InitGameWorld()
{
	font = TTF_OpenFont("Assets/Fonts/LTYPE.TTF", 30); //30 is the initial font size
	//from here
	//playerPaddle.x = 20;
	//playerPaddle.y = WINDOW_HEIGHT * 0.5 - 50; //set it just above the half of the window's center
	//playerPaddle.h = 100;
	//playerPaddle.w = 20;

	//aiPaddle.x = WINDOW_WIDTH - 40; //sets the aiPaddle 40 pixels to the left of the right-most window corner
	//aiPaddle.y = WINDOW_HEIGHT * 0.5 - 50;
	//aiPaddle.h = 100;
	//aiPaddle.w = 20;

	//ball.x = (WINDOW_WIDTH * 0.5) - 30; //around 370 pixels if window is 800 in width
	//ball.y = (WINDOW_HEIGHT * 0.5) - 10; //around the center, at about 290 pixels
	//ball.w = 20;
	//ball.h = 20;
	//till here


	//for sprite

	int destScaleWFirst = 128;
	int destScaleHFirst = 128;
	float centerXFirst = (WINDOW_WIDTH * 0.5)-200;
	float bottomPtyFirst = (WINDOW_HEIGHT - destScaleHFirst - 20);
	spriteActorStrip =InitializeSpriteActor("Assets/Sprites/spritestrip-1536.png",256,0,256,256,
		centerXFirst -(destScaleWFirst *0.5),bottomPtyFirst, destScaleWFirst, destScaleHFirst,1,6,0,true);//to maintain the original scale we pass 256 256
	//if you want to scaleit down then you can provid as smaller number fo the last two args

	// For explosion	
		int destScaleW = 182;
	    int destScaleH = 182;
		float centerX = (WINDOW_WIDTH * 0.5);
		float bottomPty = (WINDOW_HEIGHT - destScaleHFirst - 20);
		
	    spriteActor= InitializeSpriteActor("Assets/Sprites/exp.png", 182,0, 182, 182,
		centerX-(destScaleW *0.5),bottomPty, destScaleW, destScaleH,4,5,0,true);//to maintain the original scale we pass 256 256




}


void GameEngine:: RenderFont(const char* text, int x, int y, bool isRefreshText)
{
	if (isRefreshText)
	{
		SDL_Color textColor = { 255,255,255,0 }; //white color

		SDL_Surface* fontSurface = TTF_RenderText_Solid(font, text, textColor);

		//need to first de-allocate any previously assigned font-texture
		SDL_DestroyTexture(fontTexture);

		fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
		//fontRectScore = { x,y,fontSurface->w, fontSurface->h };
	}
	//draw the font
	//SDL_RenderCopy(renderer, fontTexture, 0, &fontRectScore);

}


void GameEngine :: Render()
{
	SDL_RenderClear(renderer); //clear previously drawn frame
	//from here
	////Start drawing the current frame
	////Render the Background
	////5,30,67 represents a dark blue color. Check MS Paint's edit color to get your own rgb value.
	////the fifth argument below, 255 stands for the 'alpha' i.e. transparency of the color. 255=opaque, 0=transparent
	//SDL_SetRenderDrawColor(renderer, 5, 30, 67, 255);
	//SDL_RenderFillRect(renderer, &background); //fill the background rect with the above color

	////Render the player & ai Paddle
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //draw paddles in white
	//SDL_RenderFillRect(renderer, &playerPaddle); //fill rect with above white color
	//SDL_RenderFillRect(renderer, &aiPaddle); //fill the aiPaddle rect with the above white color as well

	////Render the ball
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //draw ball with red color
	//SDL_RenderFillRect(renderer, &ball); //fill ball's rect with the above red color

	//int score = 45;
	//string s = "Score: " + to_string(score);

	//RenderFont(s.c_str(), 30, 50, true);
	// till here

	//for sprite 
	RenderSpriteActor();

	SDL_RenderPresent(renderer); //must call this to render the above defined
}

void GameEngine:: Quit()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	//shutdown SDL
	SDL_Quit();

	TTF_CloseFont(font);
	TTF_Quit();

}

void GameEngine:: Input()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEMOTION) //if mouse movement is detected
		{
			SDL_GetMouseState(&mouseX, &mouseY);
		}

		//if we click 'X' button to close the app window then SDL_QUIT event type is triggered
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}

		//check if key was pressed
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				isRunning = false;
				break;
			case SDLK_e:
				if (isExplosion)
				{
					spriteActor->setCurrentRowToInitialRow();
					spriteActor->setAnimitaedIsFinished(false);
					isExplosion = false;
				}
			break;
			case SDLK_w:
				spriteActorStrip->setCurrentRowToInitialRow();
				spriteActorStrip->setAnimitaedIsFinished(false);
				break;
			}
			
			

		}
		if (event.type == SDL_KEYUP) 
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
			 spriteActorStrip->setAnimitaedIsFinished(true);
				break;
			}
		}


	}

}

void GameEngine:: Update()
{    //from here
	//playerPaddle.y = mouseY; //map the playerPaddle's position to the mouse's y position

	////Our initial demo ball movement. to be removed and replaced with something else later.
	//ball.x += 1;
	//ball.y += 1;

	//slow down by using SDL_Delay
	//till here

	spriteActor->Update();
	spriteActorStrip->Update();
	SDL_Delay(10); //pause the game loop for 10 milliseconds to slow down the game to a decent speed

}



Sprite * GameEngine::InitializeSpriteActor(const char* loadPath, int cellx,
	int celly, int cellw, int cellh, int destx, int desty, int destw, int desth,
	int tRows, int tColumns, int initialRow, bool isAnimatable)
{

	SDL_Rect spriteSrcRect;
	spriteSrcRect.x = cellx;
	spriteSrcRect.y = celly;
	spriteSrcRect.w = cellw;
	spriteSrcRect.h = cellh;

	SDL_Rect spritePos;
	spritePos.x = destx;
	spritePos.y = desty;
	spritePos.w = destw;
	spritePos.h = desth;
	 
	return new Sprite(loadPath, spriteSrcRect, spritePos, tRows, tColumns, initialRow, isAnimatable);

}

void GameEngine::RenderSpriteActor()
{
	spriteActor->Render();
	spriteActorStrip->Render();
}

GameEngine :: ~GameEngine()
{
	delete spriteActor;
	spriteActor = nullptr;
	delete spriteActorStrip;
	spriteActorStrip = nullptr;

}