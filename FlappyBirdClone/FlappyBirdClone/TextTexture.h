#pragma once
#include <SDL_ttf.h>

#include <iostream>
#include <string>

class TextTexture
{
public:
	TextTexture(SDL_Renderer* renderer);

	void DrawText(std::string aText, int aX, int aY, int fontSize);
private:
	SDL_Renderer* renderer;
};

