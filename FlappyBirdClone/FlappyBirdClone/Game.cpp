#include "Game.h"

Game::Game()
{
	window = NULL;
	renderer = NULL;
}

Game::~Game()
{
}

bool Game::Init()
{
	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Slopey", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cout << "Failed to create window. SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		std::cout << "Failed to create renderer. SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	//Initialize TTF
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}

	//Initialize Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}

	SDL_Surface* newSurface = IMG_Load("test.png");
	texture = SDL_CreateTextureFromSurface(renderer, newSurface);
	SDL_FreeSurface(newSurface);

	countedFrames = 0;
	bestScore = 0;

	fpsTimer.start();

	return true;
}

void Game::Clean()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	texture = NULL;
	renderer = NULL;
	window = NULL;

	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
}

void Game::Run()
{	
	newGame();

	while (1)
	{
		capTimer.start();
		if (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
			{
				break;
			}
		}

		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}

		Update();
		Render();
		++countedFrames;

		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}

	Clean();
}

void Game::Update()
{
	//Handle user input
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		if (e.key.keysym.sym == SDLK_SPACE)
		{
			ball->Up();
			audio->playSound("FlappyJump.wav");			
		}
	}

	//every 75 passes spawn a pillar
	if (countedFrames % 75 == 0 && pillarList.size() < 5)
	{
		pillar = new Pillar(renderer);
   		pillarList.push_back(pillar);
	}

	//iterate through pillars
	std::list<Pillar*>::iterator currentPipe;
	for (currentPipe = pillarList.begin(); currentPipe!=pillarList.end(); currentPipe++)
	{
		//Check if pipe is off screen
		if ((*currentPipe)->x + (*currentPipe)->width < 0)
		{
			currentPipe++;
			pillarList.erase(pillarList.begin());
			incrementScore();
			audio->playSound("FlappyScore.wav");
		}
		(*currentPipe)->Update();
	}

	ball->Update();

	checkScreenCollisions(ball);

}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 188, 252, 255, 0);
	SDL_RenderClear(renderer);

	ball->Render();
	
	//Render pillars and check collisions
	for (Pillar* currentPipe : pillarList)
	{		
  		currentPipe->Render();
		if (currentPipe->checkPillarCollisions(ball->getBallRect()))
		{
			audio->playSound("FlappyDie.wav");
			newGame();
			SDL_Delay(1000);
			return;
		}
	}

	//==Text Drawing==//

	//Current Score
	textTexture->DrawText("Score: ", 0, 0, 20);
	textTexture->DrawText(std::to_string(currentScore), 100, 0, 20);

	//Best Score
	textTexture->DrawText("Best: ", 0, 30, 20);
	textTexture->DrawText(std::to_string(bestScore), 100, 30, 20);

	SDL_RenderPresent(renderer);
}

void Game::newGame()
 {
	if (currentScore > bestScore)
	{
		bestScore = currentScore;
	}
	currentScore = 0;

	//Empty list if it's not empty
	if (!pillarList.empty())
	{
		pillarList.erase(pillarList.begin(), pillarList.end());
	}

	ball = new Ball(renderer);
	textTexture = new TextTexture(renderer);
}

void Game::checkScreenCollisions(GameEntity* obj)
{
	if (obj->y < 0)
	{
		obj->y = 0;
	}
	else if (obj->y + obj->height >= SCREEN_HEIGHT)
	{
		obj->y = SCREEN_HEIGHT - obj->height;
	}
}

void Game::incrementScore()
{
	if (currentScore >= bestScore)
	{
		bestScore++;
	}
	currentScore++;
}