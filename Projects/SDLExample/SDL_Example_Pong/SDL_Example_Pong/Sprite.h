#pragma once
#include<SDL.h>
#include<SDL_image.h>


class Sprite
{
private:
	SDL_Rect spriteSrcvRec; // define what part of the spritesheet we want to render
	SDL_Rect spriteDestRect; // position on the screen we waould like to render this sprite at
	SDL_Surface* sprite;// the handle to the image 
	SDL_Texture* texture;// the texture holds the sprite texture after loading it from the sprite
	
	//by default a sprite will be static. if we nwws an animated sprite, we set to true via constructor
	bool isAnimatable = false;

	// the last column we render 
	int lastColumnNum;

	//set to true once an animation has completed playing
	bool isAnimationFinished = false;

	int currentRow;//whiche row are we surrrnetly at wheile rendering the anamation?
	int currentColumn;//whiche column are we surrrnetly at wheile rendering the anamation?
protected:
	int tRows; // total rows in our sprite sheet aniation
	int tColumns; // total colmns in our sprite sheet aniation

	float animSpead = 10; // animation speed, in pixels/unit

	
	int initalRow;


public:
	Sprite(const char* spritePath,SDL_Rect srcRect, SDL_Rect destRect,
	int totalRows, int totalColumns, int initialRowNum, bool isAnimatable);
	~Sprite();
	void Render();
	void Update();
	void setAnimitaedIsFinished(bool bol);
	void setCurrentRowToInitialRow();
};

