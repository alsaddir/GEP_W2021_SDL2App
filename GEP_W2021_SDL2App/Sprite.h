#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Sprite
{
private:
	SDL_Rect spriteSrcRect; //defines part of the spritesheet we would like to render
	SDL_Rect spriteDestRect; //position on the screen we would like to render this sprite at
	SDL_Surface* sprite; //the handle to the image
	SDL_Texture* texture; //the texture holds the sprite texture after loading it from the sprite

	//by default, a sprite will be static. If we need an animated sprite, we set this to true via constructor
	bool isAnimatable = false;

	int lastColumnNum; //the last column we rendered

	//set to true once an animation has completed playing
	bool isAnimationFinished = false;

	int currentRow; //which row are we currently at, while rendering the animation?
	int currentColumn;//which column are we currently at, while rendering the animation?

protected:
	int tRows; //total rows in our sprite sheet animation
	int tColumns; //total columsn in our sprite animation

	float animSpeed = 10; //animation speed, in pixels/unit
	
	int initialRow; //make sure this is a 0-based index


public:
	Sprite(const char* spritePath, SDL_Rect srcRect, SDL_Rect destRect, 
		int totalRows, int totalColumns, int initialRowNum, bool isAnimatable);
	~Sprite();
	void Render();
	
	void Update();

};

