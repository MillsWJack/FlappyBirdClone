#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "GameEntity.h"

class Background
{
public:
	Background(SDL_Renderer* renderer);
	~Background();

	void render();
	void moveX();

private:
	int x;
	int y;

	SDL_Rect rectQuad;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
};

