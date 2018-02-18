#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <list>
#include <time.h>
#include <sstream>

#include "Ball.h"
#include "Pillar.h"
#include "Timer.h"
#include "TextTexture.h"
#include "Audio.h"
#include "Background.h"

class Game
{
public:
	Game();
	~Game();

	bool Init();
	void Run();

	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

	const int SCREEN_FPS = 60;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	float avgFPS;

	std::list<Pillar*> pillarList;

private:

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

	Ball* ball;
	Pillar* pillar;
	Audio* audio;
	Background* bg;

	TextTexture* textTexture;
	SDL_Event e;

	Timer fpsTimer;
	Timer capTimer;

	unsigned int currentScore;
	unsigned int bestScore;
	unsigned int countedFrames;

	void Clean();
	void Update();
	void Render();
	void newGame();
	void checkScreenCollisions(GameEntity* obj);
	void incrementScore();
};

