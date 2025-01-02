#include <SFML/Graphics.hpp>

#include "Game.h"


int main()
{
    sf::Clock clock;

	Game game("Jumperboiii", &clock);

	//Main game loop
	while (game.getCurGameState() != Game::GameState::not_running)
	{
		// put pause button in handleEvents method
		// if statement starting here that checks if current game state is pause
		// if condition true
		float nextFrameStart = (float)clock.getElapsedTime().asMilliseconds() + (1000.0f / 60.0f);

		game.handleEvents();
		game.update();
		game.render();

		while ((float)clock.getElapsedTime().asMilliseconds() < nextFrameStart);
	}

	//Cleans game after it has stopped running
	game.clean();

	return 0;
}