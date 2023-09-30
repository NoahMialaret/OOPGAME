#include "Game.h"

Game::Game(const char* title) {
	window.create(sf::VideoMode(800, 600), title);

	std::cout << "Enabling standard play." << std::endl;
	cur_game_state = GameState::standard_play;
}

void Game::handleEvents() {
	sf::Event event;
	
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				std::cout << "Window close event called." << std::endl;

				cur_game_state = GameState::not_running;
				break;

			case sf::Event::Resized: {
				std::cout << "Window resize event called." << std::endl;

				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        		window.setView(sf::View(visibleArea));
				break;
			}
		}
	}
}

void Game::update() {

}

void Game::render() {
	window.clear();

	window.display();	
}

void Game::clean() {
	window.close();
	
	std::cout << "Game successfully cleaned!\n";
}



Game::GameState Game::getCurGameState() const {
	return cur_game_state;
}

void Game::enableStandardPlay() {
	std::cout << "Switching to standard play.\n";

	cur_game_state = GameState::standard_play;
}

void Game::pause() {
	std::cout << "Pausing game." << std::endl;

	cur_game_state = GameState::paused;
}

void Game::unpause() {
	std::cout << "Unpausing game." << std::endl;

	cur_game_state = GameState::standard_play;
}

void Game::gameExit() {
	std::cout << "Exiting game..." << std::endl;

	cur_game_state = GameState::not_running;
}
