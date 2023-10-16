#include <SFML/Graphics.hpp>

#include "Game.h"

Game game("Jumperboiii");

int main()
{
    sf::Clock clock;

	//Main game loop
	while (game.getCurGameState() != Game::GameState::not_running)
	{
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