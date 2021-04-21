#pragma once
#include "SpriteEx.h"

class LifePickUp : public SpriteEx
{
private:
	float rotationSpeed; // at what speed should the asteroid rotate

public:
	LifePickUp(SDL_Texture* text, SDL_Rect srcRect, SDL_Rect destRect, float rotSpeed)
		:SpriteEx(text, srcRect, destRect), rotationSpeed(rotSpeed)
	{
		m_X = destRect.x;
		m_Y = destRect.y;
		m_dRadius = 100;

	}

	void Update()
	{
		angle += rotationSpeed; //nothing fancy in here yet .. just incrementing the angle with rotationSpreed
	}

};