#include "Background.h"

Background::Background(SDL_Renderer* renderer):
	renderer(renderer)
{
	SDL_Surface* surface = IMG_Load("FlappyBG.png");
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
	x = 0;

	SDL_FreeSurface(surface);
}

Background::~Background()
{
}

void Background::render()
{
	rectQuad.x = x;
	rectQuad.y = 0;
	rectQuad.w = 3840;
	rectQuad.h = 1080;
	SDL_RenderCopy(renderer, texture, NULL, &rectQuad);
}

void Background::moveX()
{
	 x -= 10;
	 if (x + 1920 < 0)
	 {
		 x = 0;
	 }
}