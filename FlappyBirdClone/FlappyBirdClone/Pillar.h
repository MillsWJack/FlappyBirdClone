#pragma once

#include "GameEntity.h"
#include <list>

class Pillar : public GameEntity
{
public:
	Pillar(SDL_Renderer* renderer);
	~Pillar();

	void Update();
	void Render();
	bool checkPillarCollisions(SDL_Rect* obj);

private:

	SDL_Texture* texture;
	float moveSpeed;
	int top;
	int bot;
	int minimumSpace;
	SDL_Rect rectBot;
	SDL_Rect rectTop;
	SDL_RendererFlip flip;

	const int originalTextureHeight = 793;
	const int originalTextureWidth = 138;
};

