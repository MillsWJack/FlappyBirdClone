#include "GameEntity.h"

GameEntity::GameEntity(SDL_Renderer* renderer)
{
	this->renderer = renderer;

	x = 0;
	y = 0;
	width = 1;
	height = 1;
}

GameEntity::~GameEntity()
{
}

void GameEntity::Update(float delta)
{

}

void GameEntity::Render(float delta)
{

}

bool GameEntity::Collides(SDL_Rect* obj)
{
	if (x + width > obj->x && obj->x + obj->w &&
		y + width > obj->y && obj->y + obj->h)
	{
		return true;
	}

	return false;
}