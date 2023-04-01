#include "game.h"

int main()
{
	game* gameVariable = new game();

	gameVariable->play(800, 600, "Test Game");

	delete gameVariable;
}
