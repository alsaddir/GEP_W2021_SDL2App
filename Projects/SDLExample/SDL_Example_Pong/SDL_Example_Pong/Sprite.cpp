#include "Sprite.h"
#include "GameEngine.h"
Sprite::Sprite(const char* spritePath, SDL_Rect srcRect, SDL_Rect destRect,
	 int totalRows, int totalColumns, int initialRowNum, bool isAnimatable)
{
	//step1 : Load the sprite
	//IMG_Load is a part of "SDL_image.h"
	sprite = IMG_Load(spritePath);

	spriteSrcvRec = srcRect;
	spriteDestRect = destRect;

	texture = SDL_CreateTextureFromSurface(GameEngine::Instance()->GetRenderer(), sprite);

	tRows = totalRows;
	tColumns = totalColumns;
	initalRow = initialRowNum;
	this->isAnimatable = isAnimatable;

	//SET THE Y OF THE SOURCE RECT TO TIS 
	spriteSrcvRec.y = spriteSrcvRec.h * initalRow;
}

Sprite::~Sprite()
{
	SDL_FreeSurface(sprite);
	SDL_DestroyTexture(texture);

}

void Sprite::Render()
{
	SDL_RenderCopy(GameEngine :: Instance()->GetRenderer(),texture, &spriteSrcvRec, &spriteDestRect);
}

//this is to e called in sa loop via GameEngine.cpp's update function
void Sprite::Update()
{
	if (!isAnimatable) return; // if the sprite not animated then return
	if (isAnimationFinished)return; // if animation has completet then return 

	//Calculate fps(frame per second). Note: SDL_GetTicks() return value in millisecond. we divided by 1000 to get value in second
	Uint32 fps = (SDL_GetTicks() / 1000.0f) * animSpead;
	
	currentColumn = fps % tColumns;
	if (currentColumn < lastColumnNum)
	{
		currentRow++;
		std::cout << "Column"<<currentColumn;
		std::cout << "Row "<<currentRow<<"\n";
	}
	//if this happens, then it means we have cycled 
	if (currentRow >= tRows)
	{
		std::cout << "I change row Column" << currentColumn;
		std::cout << " I change row Row " << currentRow << "\n";
		currentRow++;
	}

	/// <summary>
	/// if this happens, then we are at the last row. it is time to set back
	/// to initial row num and set isAnimationFinishes= trure;
	/// </summary>
	if (currentRow >= tRows)
	{
		
		isAnimationFinished = true;
		//currentRow = initalRow;
	}

	spriteSrcvRec.x = spriteSrcvRec.w * currentColumn;
	spriteSrcvRec.y = spriteSrcvRec.h * currentRow;

	lastColumnNum = currentColumn;


}

void Sprite::setAnimitaedIsFinished(bool bol)
{
	isAnimationFinished = bol;
}

void Sprite::setCurrentRowToInitialRow()
{
	currentRow = initalRow;
}
