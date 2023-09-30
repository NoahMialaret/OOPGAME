#include "Game.h"

Game::Game(const char* title) {
	window.create(sf::VideoMode(800, 600), title);

	if (!mouse_tex.loadFromFile("art/Mouse.png")) {
		std::cout << "Texture could not be loaded!" << std::endl;
		return;
	}

	test_mouse.setTexture(mouse_tex, true);
	test_mouse.setScale(sf::Vector2f(game_scale, game_scale));

	std::cout << "Enabling standard play." << std::endl;
	cur_game_state = GameState::standard_play;

	window.setKeyRepeatEnabled(false);

	window.setMouseCursorVisible(false);
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

			case sf::Event::KeyPressed:
				std::cout << "Key press event called." << std::endl;

				switch (event.key.code) {
					case sf::Keyboard::D:
						is_d_pressed = true;
						break;

					case sf::Keyboard::A:
						is_a_pressed = true;
						break;

					case sf::Keyboard::Space:
						is_space_pressed = true;
						break;
				}
				break;
				
			case sf::Event::KeyReleased:
				std::cout << "Key released event called." << std::endl;

				switch (event.key.code) {
					case sf::Keyboard::D:
						is_d_pressed = false;
						break;

					case sf::Keyboard::A:
						is_a_pressed = false;
						break;

					case sf::Keyboard::Space:
						is_space_pressed = false;
						break;
				}
				break;
		}
	}
}

void Game::update() {
	player.update(&window, is_space_pressed, is_a_pressed, is_d_pressed);
		
	test_mouse.setPosition(mouse.getPosition(window).x, mouse.getPosition(window).y);
}

void Game::render() {
	window.clear();

	player.render(&window);
	window.draw(test_mouse);

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
