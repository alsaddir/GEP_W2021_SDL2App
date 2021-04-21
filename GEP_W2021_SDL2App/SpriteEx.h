#pragma once
#include<SDL.h>
#include<iostream>
//Base class will render just one static sprite
class SpriteEx
{
protected:
	SDL_Rect spriteSrcRect;// part of the spritesheet we would like to render
	SDL_Rect spriteDestRect; //position on the window we would like to render this sprite at
	SDL_Texture* texture; //reference to load trecture
	double angle; // the angle to display the sprite in degrees
	double m_X, //x coord
		m_Y,//y coord
		m_DX, // the change in x coord
		m_DY, // the change in y coord
		m_dSpeed; // speed in pixel to move per change
	double m_dRadius; // radius of the sprites circle bounds

public:
	SpriteEx() {}
	SpriteEx(SDL_Texture* text, SDL_Rect srcRect, SDL_Rect destRect)
		:spriteSrcRect(srcRect), spriteDestRect(destRect), texture(text)
	{

	}

	void Render();
	void UpdateDestRect();

	double GetRadius() { return m_dRadius; };
	double GetX() { return m_X; };
	double GetY() { return m_Y; };
	void SetHightAndWidth(double x) { spriteDestRect.h -= x; spriteDestRect.w -= x;};
	double GetWidth() { return spriteDestRect.w; }
	
	

	
};


//this is the animated version of the version of the SpriteEx class
// we inherit from the above class and add animation featurs
class SpriteExAnimated : public SpriteEx
{
protected :
	int m_iSprte = 0, // which sprite to display for animation
		m_iSprteMax, // how many sprites in total for this animation
		m_iFrame = 0, // which frame we are ar now
		m_iFrameMax; // numbers of frames for this sprie

public:
	void Animate();
	SpriteExAnimated(SDL_Texture* tex, double x , double y , double a , int frameMax, int spriteMax, double speed);

};

