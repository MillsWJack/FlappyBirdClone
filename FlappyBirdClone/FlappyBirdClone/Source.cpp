#include "Game.h"

int main(int argc, char* argv[])
{
	//Create game object
	Game* game = new Game();

	//Init and run
	if (game->Init())
	{
		game->Run();
	}

	//Clean up
	delete game;
	return 0;
}