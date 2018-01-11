#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class GameEntity
{
public:
	GameEntity(SDL_Renderer* renderer);
	~GameEntity();

	void Update(float delta);
	void Render(float delta);

	bool Collides(SDL_Rect* obj);

	float getXPos() { return x; }
	float getYPos() { return y; }
	float getWidth() { return width; }
	float getHeight() { return height; }

	float x;
	float y;
	float width;
	float height;

protected:
	SDL_Renderer* renderer;
};

