#include <iostream>
#include <string>
#include "Game.h"

int main()
{
	Game game;
	
	while (!game.getWindow()->isDone())
	{
		game.HandleInput();
		game.Render();
		game.Update();
		
	}

}