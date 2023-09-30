#include "Game.h"

Game::Game(const char* title) {
	window.create(sf::VideoMode(800, 600), title);
    
	if (!player_tex.loadFromFile("art/TestCharacter.png")) {
		std::cout << "Texture could not be loaded!" << std::endl;
		return;
	}

	test_player.setTexture(player_tex, true);
	test_player.setScale(sf::Vector2f(game_scale, game_scale));

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
	if (!is_space_pressed) {
		jump_hold = false;
	}

	// Continues adding jump height if the jump button is held
	if (is_space_pressed && can_increase_jump_velocity && velocity.y > -15.0f) {
		velocity.y -= 2.5f;
	} 
	else {
		can_increase_jump_velocity = false;
	}

	// Initial jump velocity
	if (!jump_hold && is_space_pressed && is_grounded) {
		velocity.y = -5.0f;
		is_grounded = false;
		can_increase_jump_velocity = true;
		jump_hold = true;
	}

	// Effect of gravity on the player
	velocity.y += 0.8f;

	// Horizontal velocity calculation, varies depending on whether the player is gorunded or not
	if (is_d_pressed != is_a_pressed) { // i.e. if only one of them is pressed
		float speed_modifier = 1.0f - !is_grounded * 0.5f;

		velocity.x += is_d_pressed * speed_modifier - is_a_pressed * speed_modifier;
		
		velocity.x = std::clamp(velocity.x, -10.0f, 10.0f);
	}
	else { // if both or neither buttons are pressed
		if (velocity.x > 0.0f) {
			velocity.x -= is_grounded ? 1.0f : 0.2f;
			if (velocity.x < 0.0f) {
				velocity.x = 0.0f;
			}
		}
		else if (velocity.x < 0.0f) {
			velocity.x += is_grounded ? 1.0f : 0.2f;
			if (velocity.x > 0.0f) {
				velocity.x = 0.0f;
			}
		}
	}

	test_player.move(velocity);

	if (test_player.getPosition().y > (float)window.getSize().y - sprite_dimensions * game_scale) {
		is_grounded = true;
		velocity.y = 0.0f;
	}
	if (test_player.getPosition().x < 0.0f || test_player.getPosition().x > (float)window.getSize().x - sprite_dimensions * game_scale) {
		velocity.x = 0.0f;
	}

	sf::Vector2f pos(0.0f, 0.0f);
	pos.x = std::clamp(test_player.getPosition().x, 0.0f, (float)window.getSize().x - sprite_dimensions * game_scale);
	pos.y = std::clamp(test_player.getPosition().y, 0.0f, (float)window.getSize().y - sprite_dimensions * game_scale);
	test_player.setPosition(pos);

	test_mouse.setPosition(mouse.getPosition(window).x, mouse.getPosition(window).y);
}

void Game::render() {
	window.clear();

	window.draw(test_player);
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
