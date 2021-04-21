#pragma once
#include "SpriteEx.h"
#include "SDL.h"
#include "SDL_image.h"

#include "SDL_mixer.h"  //required for audio

#include <vector>
#include "Asteroid.h"
#include "Player.h"
#include "SDL_ttf.h"
#include <string>


#include "StateMachine.h"

using namespace std;

class Game
{
private:
	bool isAppRunning;
	SDL_Window* sdlWindow;
	SDL_Renderer* sdlRenderer;
	const Uint8* m_iKeystates; //manages keystates

	StateMachine * m_pFSM; 

	SDL_Texture* mainSpriteTex;//load and store the main sprite texture
	SDL_Texture* bgSpriteTex; //load and store background sprite tex


	SpriteEx* bg;

	Player* player;
	vector<Asteroid*> asteroids;

	Mix_Chunk* fireSound;
	Mix_Chunk* engineSound;

	SDL_Texture* LoadTexture(const char* path);

	float lives = 3;
	int score = 0;

	TTF_Font * m_pFont;
	SDL_Texture *m_pFontTexture;
	SDL_Rect m_rFontRectScore;

	void RenderFont(bool isRefreshText, const char *text, int x, int y);

	bool m_bLeftMouse = false; // Keeps track of left mouse button state.
	int m_iMouseX, m_iMouseY;  // Variables to hold mouse positions.


public:
	static Game* Instance(); //singleton instance reference
	SDL_Window* GetWindow() { return sdlWindow; }
	SDL_Renderer* GetRenderer() { return sdlRenderer; }
	

	//window initialization happens here
	bool Init(const char* title, const int xPos,
		const int yPos, const int width, const int height,
		const int flags);

	void QuitGame() { isAppRunning = false; }
	void InitializeGame();

	//Is the Application running
	bool IsRunning();
	//Check for 'KeyDown' press
	bool KeyDown(SDL_Scancode c);
	bool KeyUp(SDL_Scancode c);

	//The update loop
	void Update();
	//Handles input events
	void HandleEvents();
	//handles rendering
	void Render();
	//clean-up code
	void Clean();


	bool CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2)
	{
		return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (r1 + r2));

	}

	void CheckCollision();

	int GetMouseX() { return m_iMouseX; }
	int GetMouseY() { return m_iMouseY; }
	int GetLeftMouse() { return m_bLeftMouse; }
	void SetLeftMouse(bool b) { m_bLeftMouse = b; }

	StateMachine* GetFSM() { return m_pFSM; }
};