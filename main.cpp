#include <SFML/Graphics.hpp>

#include "Game.h"

Game game("Test");

int main()
{
    sf::Clock clock;

	//creating the play button:
	sf::Texture play_button_tex;
	if(!play_button_tex.loadFromFile("art/playButton.png")) {
		std::cout << "play button texture couldn't load" << std::endl;
	}
	Button play_button(&play_button_tex, 300, 400);
	game.startGameplay(&play_button);

	

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