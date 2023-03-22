#include "Game.h"
void main()
{
	int Width = 1920;
	int Height = 1280;
	Game* game = new Game(Width, Height);
	delete game;
}