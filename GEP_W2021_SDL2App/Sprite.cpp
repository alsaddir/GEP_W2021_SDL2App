#include "Sprite.h"
#include "GameEngine.h"

Sprite::Sprite(const char* spritePath, SDL_Rect srcRect, SDL_Rect destRect
	,int totalRows, int totalColumns, int initialRowNum, bool isAnimatable
)
{
	//Step 1: Load the sprite
	//IMG_Load is a part of "SDL_image.h" (you need to add sdl2_image package via nuget package manager)
	sprite = IMG_Load(spritePath);

	spriteSrcRect = srcRect;
	spriteDestRect = destRect;
	
	//we create texture from the sprite "surface" using SDL_CreateTextureFromSurface() function
	texture = SDL_CreateTextureFromSurface(GameEngine::Instance()->GetRenderer(), sprite);

	tRows = totalRows;
	tColumns = totalColumns;
	initialRow = initialRowNum;
	this->isAnimatable = isAnimatable;  //don't forget to add this-> to make sure we set isAnimatable field to the isAnimatable value coming in via the arg

	//set the y of the source rect to this:
	spriteSrcRect.y = spriteSrcRect.h * initialRow;

}

Sprite::~Sprite()
{
	SDL_FreeSurface(sprite);
	SDL_DestroyTexture(texture);
}

void Sprite::Render()
{
	SDL_RenderCopy(GameEngine::Instance()->GetRenderer(), texture, &spriteSrcRect, &spriteDestRect);
}

//this is to be called in a loop via GameEngine.cpp's Update function
void Sprite::Update()
{
	if (!isAnimatable) return; //if the sprite is not animatable, then return
	if (isAnimationFinished) return; //if animation has been completed, return

	//Calculate fps. Note: SDL_GetTicks() returns value in milliseconds. We divide by 1000 to get value in seconds
	Uint32 fps = (SDL_GetTicks() / 1000.0f) * animSpeed;


	
	currentColumn = fps % tColumns;
	
 
	//if this happens, then it means we have cycled through an entire row
	if (currentColumn < lastColumnNum)
	{
		currentRow++; //it's time to move to the next row
	}

	/// <summary>
	///if this happens, then we are at the last row. it's time to set back to the initial row num and set isAnimationFinished=true
	/// </summary>
	if (currentRow >= tRows)
	{
		isAnimationFinished = true; //set to true if it is not loopable
		currentRow = initialRow; //reset for next animation loop/play request
	}

	spriteSrcRect.x = spriteSrcRect.w * currentColumn; 
	spriteSrcRect.y = spriteSrcRect.h * currentRow;

	lastColumnNum = currentColumn;


}
