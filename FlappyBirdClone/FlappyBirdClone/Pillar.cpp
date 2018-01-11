#include "Pillar.h"

Pillar::Pillar(SDL_Renderer* renderer) : GameEntity(renderer)
{
	SDL_Surface* surface = IMG_Load("pipe.png");
	if (surface == NULL)
	{
		std::cout << "Failed to load surface. SDL_Error: " << SDL_GetError() << std::endl;
		return;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL)
		{
			std::cout << "Failed to create texture from surface. SDL_Error: " << SDL_GetError() << std::endl;
			return;
		}
	}
	SDL_FreeSurface(surface);

	x = 1920;
	y = 0;
	width = 138;

	minimumSpace = 287;

	//Get random position for top of empty space
	top = -1 * (rand() % originalTextureHeight);
	//Get position for bottom of empty space based off of top 
	//+ minimum space
	bot = (top + originalTextureHeight) + minimumSpace;

	moveSpeed = 15;	
}

Pillar::~Pillar()
{
}

void Pillar::Update()
{
	x -= moveSpeed;
}

void Pillar::Render()
{	
	rectBot.x = x;
	rectBot.y = bot;
	rectBot.w = width;
	rectBot.h = originalTextureHeight;
	SDL_RenderCopy(renderer, texture, NULL, &rectBot);

	rectTop.x = x;
	rectTop.y = top;
	rectTop.w = width;
	rectTop.h = originalTextureHeight;
	SDL_RenderCopyEx(renderer, texture, NULL, &rectTop, 180, NULL, flip);
}

bool Pillar::checkPillarCollisions(SDL_Rect* obj)
 {
	if (SDL_HasIntersection(&rectTop, obj))
	{
 		return true;
	}
	if (SDL_HasIntersection(&rectBot, obj))
	{
  		return true;
	}

	return false;
}