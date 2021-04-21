#include "SpriteEx.h"
#include "GameEngine.h"

void SpriteEx::Render()
{
	
		SDL_RenderCopyEx(GameEngine::Instance()->GetRenderer(),texture,
			&spriteSrcRect,&spriteDestRect,angle, nullptr, SDL_FLIP_NONE) ;
	//std::cout << "success.... \n";
 //else
	//std::cout<<"fail..\n";
}

void SpriteEx::UpdateDestRect()
{
	spriteDestRect.x = (int)(m_X - spriteDestRect.w * 0.5f);
	spriteDestRect.y = (int)(m_Y - spriteDestRect.h * 0.5f);
}

void SpriteExAnimated::Animate()
{
	m_iFrame++;
	if (m_iFrame == m_iFrameMax)
	{
		m_iFrame = 0;
		m_iSprte++;
		if (m_iSprte == m_iSprteMax)
			m_iSprte = 0;
	}
	
}

SpriteExAnimated::SpriteExAnimated(SDL_Texture* tex, double x, double y, double a, int frameMax, int spriteMax, double speed)
{
	texture = tex;
	m_X = x;
	m_Y = y;
	angle = a;
	m_iFrameMax = frameMax;
	m_iSprteMax = spriteMax;
	m_dSpeed = speed;
}
