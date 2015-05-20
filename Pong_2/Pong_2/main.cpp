#include "Pong.h"

int main(int argc, char* args[])
{
	Pong game;
	if (game.init() == true)
	{
		game.run();
	}
	return 0;
}