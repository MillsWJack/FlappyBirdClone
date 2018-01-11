#include "Ball.h"

Ball::Ball(SDL_Renderer* renderer) : GameEntity(renderer)
{
	SDL_Surface* surface = IMG_Load("ball.png");
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

	x = 100;
	y = 100;
	width = 50;
	height = 50;
	gravity = 0.5;
	acceleration = 0;
	angle = 0;
}

Ball::~Ball()
{
	SDL_DestroyTexture(texture);
}

void Ball::Update()
{
	acceleration += gravity;
	y += acceleration;

	//Cap acceleration
	handleAcceleration();

	//Check whether falling or jumping
	checkStatus();

	//Animation Angle handling
	handleAnimation();
}

void Ball::Render()
{
	ballRect.x = x;
	ballRect.y = y;
	ballRect.w = width;
	ballRect.h = height;
	SDL_RenderCopyEx(renderer, texture, NULL, &ballRect, angle, center, flip);
}

void Ball::Up()
{
	//move up
	acceleration -= 20;
	handleAcceleration();
}

void Ball::handleAnimation()
{
	if (isFalling)
	{
		angle += 1.2;
		if (angle > 60)
		{
			angle = 60;
		}
	}
	else if (isJumping)
	{
		angle = -20;
		angle -= 1.5;
		if (angle < -40)
		{
			angle = -40;
		}
	}
}

void Ball::handleAcceleration()
{
	if (acceleration < -15)
	{
		acceleration = -15;
	}
	else if (acceleration > 15)
	{
		acceleration = 15;
	}
}

void Ball::checkStatus()
{
	if (acceleration > 0)
	{
		isFalling = true;
		isJumping = false;
	}
	else
	{
		isFalling = false;
		isJumping = true;
	}
}