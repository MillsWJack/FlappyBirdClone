#pragma once

#include "GameEntity.h"

class Ball : public GameEntity
{
public:
	Ball(SDL_Renderer* renderer);
	~Ball();

	void Update();
	void Render();
	void Up();
	void handleAnimation();
	void handleAcceleration();
	void checkStatus();

	SDL_Rect* getBallRect() { return &ballRect; }

	float getGravity() { return gravity; }
	float getAcceleration() { return acceleration; }

private:
	SDL_Texture* texture;
	SDL_Rect ballRect;

	double angle;

	SDL_Point* center;
	SDL_RendererFlip flip;

	float gravity;
	float acceleration;

	bool isFalling;
	bool isJumping;

};

