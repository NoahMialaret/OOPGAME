#include "Game.h"

Game::Game(const char* title) 
	:
    rng(std::random_device()())
{
	window.create(sf::VideoMode(800, 600), title);

	window.setKeyRepeatEnabled(false);

	window.setMouseCursorVisible(false);

	main_view = window.getDefaultView();

	if (!mouse_tex.loadFromFile("art/Mouse.png")) {
		std::cout << "Texture could not be loaded!" << std::endl;
		return;
	}

	test_mouse.setTexture(mouse_tex, true);
	test_mouse.setScale(sf::Vector2f(game_scale, game_scale));

	std::cout << "Enabling standard play." << std::endl;
	cur_game_state = GameState::standard_play;
  
	level = std::make_unique<Level>(game_scale, sprite_dimensions);
  
	player = new Player("art/TestCharacter.png", game_scale, sf::Vector2f(0.0f,50.0f));

	for (int i = 0; i < 3; i++)	{
		enemies.push_back(new Enemy("art/TestEnemy.png", game_scale));
	}
	shuffleEnemies();
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

					case sf::Keyboard::R:
						player->reset();
						break;

					case sf::Keyboard::LShift:
						shuffleEnemies();
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

	for (auto& i : enemies) {
		sf::Vector2f prev_pos = i->getPosition();
		i->update(&window);
		handleCollision(i, prev_pos);
	}

	sf::Vector2f prev_pos = player->getPosition();
	player->update(&window, is_space_pressed, is_a_pressed, is_d_pressed);
	handleCollision(player, prev_pos);

	updateMainView();
}

void Game::render() {
	window.clear();

	level.get()->render(&window);
  
	for (auto& i : enemies) {
		i->render(&window);
	}

	player->render(&window);

	window.draw(test_mouse);

	window.display();	
}

void Game::handleCollision(Entity* ent, sf::Vector2f prev_pos) {

	if (level == nullptr) {
		std::cout << "Checking for collision, but no level has been loaded!" << std::endl;
		return;
	}

	ent->setGrounded(false);

	sf::Vector2f cur_pos = ent->getPosition();

	bool is_x_negative = cur_pos.x < 0;
	bool is_y_negative = cur_pos.y < 0;
	sf::Vector2i cur_grid_pos = sf::Vector2i((int)cur_pos.x / (game_scale * sprite_dimensions) - is_x_negative, 
		(int)cur_pos.y / (game_scale * sprite_dimensions) - is_y_negative);
	
	sf::Vector2f col_pos((cur_grid_pos.x + 1) * game_scale * sprite_dimensions, (cur_grid_pos.y + 1) * game_scale * sprite_dimensions);

	std::vector<int> col = level.get()->getSurroundingCollision(cur_grid_pos);

	if (col[0] == 0 && col[1] == 0 && col[2] == 0 && col[3] == 0)
	{
		return;
	}

	// Collision check in the case of a wall or floor
	if (col[1] != 0 && col[3] != 0) {
		collision_y_correction(ent, col[3], col[1], cur_pos.y, col_pos.y);
		return;
	}
	else if (col[0] != 0 && col[2] != 0) {
		collision_x_correction(ent, col[0], col[2], cur_pos.x, col_pos.x);
		return;
	}

	bool prioritise_y_correction = (prev_pos.x < col_pos.x && (col[0] == 1 || col[2] == 1)) || (prev_pos.x + game_scale * sprite_dimensions > col_pos.x && (col[0] == -1|| col[2] == -1));

	if (prioritise_y_correction) {
		collision_y_correction(ent, col[3], col[1], cur_pos.y, col_pos.y);
	}
	else {
		collision_x_correction(ent, col[0], col[2], cur_pos.x, col_pos.x);
	}

	cur_pos = ent->getPosition();

	if (col[1] != 0 && cur_pos.x + game_scale * sprite_dimensions > col_pos.x || col[3] != 0 && cur_pos.x < col_pos.x ) {
		collision_y_correction(ent, col[3], col[1], cur_pos.y, col_pos.y);
	}
	else if (col[0] != 0 && cur_pos.y + game_scale * sprite_dimensions > col_pos.y || col[2] != 0 && cur_pos.y < col_pos.y ) {
		collision_x_correction(ent, col[0], col[2], cur_pos.x, col_pos.x);
	}
}

void Game::clean() {
	window.close();
	
	delete player;

	for(auto& i : enemies) {
		delete i;
	}

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

void Game::collision_y_correction(Entity *ent, int left_col_dir, int right_col_dir, float ent_y, float col_y) {
	int dir = left_col_dir == 0 ? right_col_dir : left_col_dir;
	if (dir == -1)
	{
		ent->setGrounded(true);
	}

	float offset = dir == 1 ? (col_y - ent_y) : (col_y - ent_y) - game_scale * sprite_dimensions;

	ent->setVelocity(sf::Vector2f(ent->getVelocity().x, 0.0f));
	ent->move(sf::Vector2f(0.0f, offset));
}

void Game::collision_x_correction(Entity *ent, int top_col_dir, int bottom_col_dir, float ent_x, float col_x) {
	int dir = top_col_dir == 0 ? bottom_col_dir : top_col_dir;
	
	float offset = dir == 1 ? (col_x - ent_x) : (col_x - ent_x) - game_scale * sprite_dimensions;

	ent->setVelocity(sf::Vector2f(0.0f, ent->getVelocity().y));
	ent->move(sf::Vector2f(offset, 0.0f));
}

void Game::shuffleEnemies() {
	std::vector<sf::Vector2i> spawns;

	for (auto& i : enemies) {
		sf::Vector2i spawn_grid_pos;
		bool can_spawn = false;

		while (!can_spawn) {
			can_spawn = true;
			spawn_grid_pos = level.get()->getValidSpawnPos(rng);
			for (int i = 0; i < spawns.size(); i++) {
				if (spawn_grid_pos == spawns[i]) {
					can_spawn = false;
					break;
				}
			}
		}

		spawns.push_back(spawn_grid_pos);
		sf::Vector2f spawn_pos(game_scale * sprite_dimensions * spawn_grid_pos.x, game_scale * sprite_dimensions * spawn_grid_pos.y);
		i->teleport(spawn_pos);
	}
}

void Game::updateMainView() {
	sf::Vector2f player_centre(player->getPosition().x + game_scale * sprite_dimensions / 2, player->getPosition().y + game_scale * sprite_dimensions / 2);
	main_view.setCenter(player_centre);

	if(main_view.getCenter().y + main_view.getSize().y / 2 > level.get()->getLevelDim().y * game_scale * sprite_dimensions) {
		main_view.setCenter(main_view.getCenter().x, (level.get()->getLevelDim().y * game_scale * sprite_dimensions) - main_view.getSize().y / 2);
	}

	if(main_view.getCenter().x - main_view.getSize().x / 2 < 0) {
		main_view.setCenter(main_view.getSize().x / 2, main_view.getCenter().y);
	}
	else if (main_view.getCenter().x + main_view.getSize().x / 2 > level.get()->getLevelDim().x * game_scale * sprite_dimensions) {
		main_view.setCenter((level.get()->getLevelDim().x * game_scale * sprite_dimensions)- main_view.getSize().x / 2, main_view.getCenter().y);
	}
	window.setView(main_view);

	test_mouse.setPosition(window.mapPixelToCoords(mouse.getPosition(window)));
}