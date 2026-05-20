#pragma once
#include <iostream>

// Singleton that sets the gravity etc. should only be set once but called many times
class Game
{
private:
	Game()
	{
		std::cout << "Game singleton created" << std::endl;
	}

	// Delete copy constructor and assignment to prevent clones
	Game(const Game&) = delete;
	
};