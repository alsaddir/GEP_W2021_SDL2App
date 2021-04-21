#pragma once
#include"SDL.h"
#include <SDL_ttf.h>
#include <iostream>
#include<string>
#include "Sprite.h"
using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class GameEngine {
private:
	bool isRunning = true;
	bool isExplosion = true;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event; //to handle events

	/*
	* Define a  sprite actor
	*/
	Sprite* spriteActor;
	Sprite* spriteActorStrip;
	Sprite* InitializeSpriteActor(const char* loadPath , int cellx, int celly, int cellw,
		int cellh,int sheetSizedestx, int desty, int destw , int desth,
		int tRows, int tColumns, int initialRow, bool isAnimatable);
	void RenderSpriteActor();


	/*Font-related declarations start*/
	TTF_Font* font;
	SDL_Texture* fontTexture;
	void RenderFont(const char* text, int x, int y, bool isRefreshText);
	/**Font-related declarations end**/

	int mouseX, mouseY; //for mouse coords
	/*
	* from here	
	SDL_Rect fontRectScore; //this defines the position of our 'score' text on the screen
	SDL_Rect playerPaddle;
	SDL_Rect aiPaddle;
	SDL_Rect ball;
	
	* till here
	*/
	SDL_Rect background = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
	//singleton pattern for GameEngine class

	

public:
	static GameEngine* Instance();
	bool InitGameEngine();
	void InitGameWorld();
	void Input();
	void Update();
	void Render();
	void Quit();
	SDL_Renderer* GetRenderer() { return renderer; }
	bool IsRunning() { return isRunning; }
	~GameEngine();



};