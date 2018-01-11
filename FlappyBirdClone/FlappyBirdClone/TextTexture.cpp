#include "TextTexture.h"

TextTexture::TextTexture(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void TextTexture::DrawText(std::string aText, int aX, int aY, int fontSize)
{
	TTF_Font* font = TTF_OpenFont("JackPixel.ttf", fontSize);

	SDL_Color fg = { 0,0,0 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, aText.c_str(), fg);

	SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect sizeRect;
	sizeRect.x = 0;
	sizeRect.y = 0;
	sizeRect.w = surface->w;
	sizeRect.h = surface->h;

	SDL_Rect posRect;
	posRect.x = aX;
	posRect.y = aY;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_RenderCopy(renderer, optimizedSurface, &sizeRect, &posRect);
	SDL_DestroyTexture(optimizedSurface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}