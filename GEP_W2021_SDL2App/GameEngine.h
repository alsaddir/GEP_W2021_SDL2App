#pragma once

#include "SDL.h"
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "SpriteEx.h"
#include "Asteroid.h"
#include "LifePickUp.h"
#include <vector>
#include <SDL_Mixer.h>
#include<SDL_image.h>
#include"Player.h"
#include "StateMachine.h"
using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


class GameEngine
{
private:
	bool isRunning = true;
	SDL_Window* window;
	SDL_Renderer* renderer;
	
	 //to handle events

	//Statemachine
	StateMachine* m_pFSM;



	//Player* player;



		//SDL_Texture* mainSpriteTex;//load and store reference to the main sprite texture
		//SDL_Texture* bgSpriteTex; // load and store background sprite tex reference

		//SpriteEx* bg; // bg sprite to be draw
	vector<Asteroid*> asteroids;// a vector  of astroides we will have in the game
	vector<Asteroid*> lifes;
	




	/* mouse fiels */
	bool m_bLeftMouse = false; // Keeps track of left mouse button state.
	int m_iMouseX, m_iMouseY;  // Variables to hold mouse positions.



	int mouseX, mouseY; //for mouse coords
	SDL_Event event;
	
	const Uint8* m_iKeystates; //manages keystates

	//	SDL_Rect background = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };


public:
	//This function returns the static instance we create the first time it is called.
	//All subsequent calls to the Instance() simply returns our first created GameEngine instance
	SDL_Texture* LoadTexture(const char* path);
	static GameEngine* Instance();

	bool IsRunning() { return isRunning; }
	void QuitGame() { isRunning = false; }
	bool InitGameEngine();
	void InitGameWorld();

	SDL_Renderer* GetRenderer() { return renderer; }

	void Input();
	void Update();
	void Render();
	void Quit();

	//bool CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2)
	//{
	//	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (r1 + r2));


	//}
	//void CheckCollision();

	int GetMouseX() { return m_iMouseX; }
	int GetMouseY() { return m_iMouseY; }
	int GetLeftMouse() { return m_bLeftMouse; }
	void SetLeftMouse(bool b) { m_bLeftMouse = b; }
	SDL_Window* GetWindow() { return window; }

	StateMachine* GetFSM() { return m_pFSM; }
	SDL_Event GetEvent(){return event;}
	bool KeyDown(SDL_Scancode c);
	bool KeyUp(SDL_Scancode c);
};
