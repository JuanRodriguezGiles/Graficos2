#include "game.h"

int main()
{
	game* gameVariable = new game();

	gameVariable->play(1600, 1200, "Game");

	delete gameVariable;
}
