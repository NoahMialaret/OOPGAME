#include "Game.h"

Game::Game(const char* title) 
	:
    rng(std::random_device()())
{
	window.create(sf::VideoMode(800, 600), title, sf::Style::Close);

	window.setPosition(sf::Vector2i(100.0f, 100.0f));

	window.setKeyRepeatEnabled(false);

	window.setMouseCursorVisible(false);

	main_view = window.getDefaultView();

	if (!mouse_tex.loadFromFile("art/Mouse.png")) {
		std::cout << "Texture could not be loaded!" << std::endl;
		return;
	}

	mouse_sprite.setTexture(mouse_tex, true);
	mouse_sprite.setScale(sf::Vector2f(game_scale, game_scale));

	std::cout << "Enabling Action Menu play." << std::endl;
	cur_game_state = GameState::action_menu;
  
	level = std::make_unique<Level>(game_scale, sprite_dimensions);
  
	sf::Vector2i spawn_grid_pos = level.get()->getValidSpawnPos(rng);
	sf::Vector2f spawn_pos(game_scale * sprite_dimensions * spawn_grid_pos.x, game_scale * sprite_dimensions * spawn_grid_pos.y);

	player = new Player("art/TestCharacter.png", game_scale, spawn_pos);

	Weapon* test = new BasicBow(player->getArrows(), game_scale);

	player->giveWeapon(test);

	Weapon* test1 = new MultiBow(player->getArrows(), game_scale);

	player->giveWeapon(test1);

	Weapon* test2 = new CrossBow(player->getArrows(), game_scale);

	player->giveWeapon(test2);

	Weapon* test3 = new BroardSword(game_scale);

	player->giveWeapon(test3);

	Weapon* test4 = new Daggers(game_scale);

	player->giveWeapon(test4);

	Weapon* test5 = new ShortSword(game_scale);

	player->giveWeapon(test5);

	ui = GameUI(player->getHealth(), player->getArrows());
	ui.setSprites(game_scale);

	for (int i = 0; i < 20; i++)	{
		enemies.push_back(new Enemy("art/TestEnemy.png", game_scale));
	}
	shuffleEnemies();

	main_ui_list.push_back("Move");
	main_ui_list.push_back("Weapon");
	main_ui_list.push_back("Item");
	main_ui_list.push_back("View Level");
	main_ui_list.push_back("End Turn");
}

void Game::handleEvents() {
	sf::Event event;
	
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				std::cout << "Window close event called." << std::endl;

				cur_game_state = GameState::not_running;
				break;

			// case sf::Event::Resized: {
			// 	std::cout << "Window resize event called." << std::endl;

			// 	sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        	// 	window.setView(sf::View(visibleArea));
			// 	main_view = window.getDefaultView();
			// 	break;
			// }

			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button) {
					case sf::Mouse::Left:
						if (!mouse_hold) {
							is_mouse_pressed = true;
							mouse_hold = true;
						}
						break;
				}
				break;
				
			case sf::Event::MouseButtonReleased:
				switch (event.mouseButton.button) {
					case sf::Mouse::Left:
						mouse_hold = false;
						break;
				}
				break;

			case sf::Event::KeyPressed:
				//std::cout << "Key press event called." << std::endl;

				switch (event.key.code) {
					case sf::Keyboard::D:
						is_d_pressed = true;
						break;

					case sf::Keyboard::A:
						is_a_pressed = true;
						break;

					case sf::Keyboard::W:
						is_w_pressed = true;
						break;

					case sf::Keyboard::S:
						is_s_pressed = true;
						break;

					case sf::Keyboard::Space:
						is_space_pressed = true;
						break;

					// case sf::Keyboard::R:
					// 	player->reset();
					// 	break;

					// case sf::Keyboard::LShift:
					// 	shuffleEnemies();
					// 	break;

					case sf::Keyboard::Escape:
						is_escape_pressed = true;
						break;
				}
				break;
				
			case sf::Event::KeyReleased:
				//std::cout << "Key released event called." << std::endl;

				switch (event.key.code) {
					case sf::Keyboard::D:
						is_d_pressed = false;
						break;

					case sf::Keyboard::A:
						is_a_pressed = false;
						break;

					case sf::Keyboard::W:
						is_w_pressed = false;
						break;

					case sf::Keyboard::S:
						is_s_pressed = false;
						break;

					case sf::Keyboard::Space:
						is_space_pressed = false;
						break;

					case sf::Keyboard::Escape:
						is_escape_pressed = false;
						break;
				}
				break;
		}
	}
}

void Game::update(sf::Clock& clock) {

	if (is_player_dead) {
		cur_game_state = GameState::not_running;
		std::cout << "Player is dead, closing game!" << std::endl;
		return;
	}

	for (auto& i : enemies) {
		sf::Vector2f prev_pos = i->getPosition();
		i->update(&window);
		handleCollision(i, prev_pos);
	}

	if (cur_weapon == nullptr) {
		sf::Vector2f prev_pos = player->getPosition();
		if (cur_game_state == GameState::moving || cur_game_state == GameState::challenge_mode) {
			player->update(is_space_pressed, is_a_pressed, is_d_pressed);
		}
		else {
			player->update();
		}
		handleCollision(player, prev_pos);

		if (player->getPosition().y > level.get()->getLevelDim().y * game_scale * sprite_dimensions) {
			std::cout << "Player fell into a pit! Reseting player." << std::endl;
			if (player->takeDamage(1)) {
				is_player_dead = true;
			}
			player->reset();

			cur_game_state = GameState::action_menu;
		}
	}

	if (cur_game_state != GameState::level_viewer) {
		updateMainView();
	}

	switch (cur_game_state)
	{
	case GameState::moving:
	case GameState::challenge_mode:
		if(is_escape_pressed || counter.update(clock)) {
			cur_game_state = GameState::action_menu;
			has_moved = true;
		}
		break;

	case GameState::attacking:
		if (is_escape_pressed) {
			if (cur_weapon->isAttacking()) {
				std::cout << "Can't put away weapon, it is currently attacking!" << std::endl;
				is_escape_pressed = false;
				return;
			}
			std::cout << "Putting away the weapon." << std::endl;
			cur_weapon->reset();
			cur_weapon = nullptr;
			cur_game_state = GameState::weapons_list;
			is_escape_pressed = false;
		}
		else if (!cur_weapon->isAttacking()) {
			cur_weapon->updateWeapon(mouse_sprite.getPosition());
			if (is_mouse_pressed) {
				cur_weapon->commenceAttack();
			}
		}
		else { // Weapon is attacking
			if (cur_weapon->updateAttack()) {
				cur_weapon->reset();
				cur_weapon = nullptr;
				ui.resetList();
				cur_game_state = GameState::enemy_turn;
			}
			else {
				weaponCollisions();
			}
		}
		break;

	case GameState::weapons_list:
	{
		if (is_escape_pressed) {
			ui.resetList();
			cur_game_state = GameState::action_menu;
		}
		int list_index = ui.update(mouse_sprite.getPosition());

		if (is_mouse_pressed && list_index != -1) {
			cur_weapon = player->getWeapon(list_index);
			cur_game_state = GameState::attacking;
		}
		break;
	}

	case GameState::enemy_turn:
		shuffleEnemies();
		has_moved = false;
		cur_game_state = GameState::action_menu;
		break;
	
	case GameState::action_menu:
	{
		if (ui.isListEmpty() && player->isStill()) {
			sf::Vector2f list_position = sf::Vector2f(window.getView().getCenter().x - window.getSize().x / 2, window.getView().getCenter().y + window.getSize().y / 2);
			ui.makeList(main_ui_list, list_position);
			is_mouse_pressed = false;
			return;
		}

		int list_index = ui.update(mouse_sprite.getPosition());

		if (!is_mouse_pressed) {
			return;
		}

		switch (list_index)
		{
		case -1: // Nothing
			std::cout << "Nothing was pressed..." << std::endl;
			break;

		case 0: // Move
			if(has_moved) {
				std::cout << "Can't move, you have already moved this turn!" << std::endl;
			}
			else {
				std::cout << "Move selected" << std::endl;
				cur_game_state = GameState::moving;

				counter = Counter(clock, 5);
				counter.setSprite(game_scale);
				ui.resetList();
			}
			break;

		case 1: // Weapons
		{
			std::cout << "Showing weapons..." << std::endl;
			ui.resetList();
			sf::Vector2f list_position = sf::Vector2f(window.getView().getCenter().x - window.getSize().x / 2, window.getView().getCenter().y + window.getSize().y / 2);
			ui.makeList(player->getWeaponNames(), list_position);
			cur_game_state = GameState::weapons_list;
			break;
		}

		case 2: // Items
			std::cout << "showing items..." << std::endl;
			break;

		case 3: // View Level
			std::cout << "Entering level viewer..." << std::endl;
			cur_game_state = GameState::level_viewer;
			break;

		case 4: // End Turn
			std::cout << "Ending turn..." << std::endl;
			cur_game_state = GameState::enemy_turn;
			break;
		
		default:
			break;
		}
		break;
	}

	case GameState::level_viewer:
	{
		if (is_escape_pressed) {
			ui.resetList();
			cur_game_state = GameState::action_menu;
		}
		float speed = 8.0f;
		sf::Vector2f move( is_d_pressed * speed - is_a_pressed * speed, is_s_pressed * speed - is_w_pressed * speed);
		main_view.move(move);

		if(main_view.getCenter().y - main_view.getSize().y / 2 < - 100.0f) {
			main_view.setCenter(main_view.getCenter().x, main_view.getSize().y / 2 - 100.0f);
		}
		else if (main_view.getCenter().y + main_view.getSize().y / 2 > level.get()->getLevelDim().y * game_scale * sprite_dimensions) {
			main_view.setCenter(main_view.getCenter().x, (level.get()->getLevelDim().y * game_scale * sprite_dimensions) - main_view.getSize().y / 2);
		}

		if(main_view.getCenter().x - main_view.getSize().x / 2 < 0.0f) {
			main_view.setCenter(main_view.getSize().x / 2, main_view.getCenter().y);
		}
		else if (main_view.getCenter().x + main_view.getSize().x / 2 > level.get()->getLevelDim().x * game_scale * sprite_dimensions) {
			main_view.setCenter((level.get()->getLevelDim().x * game_scale * sprite_dimensions)- main_view.getSize().x / 2, main_view.getCenter().y);
		}
		
		window.setView(main_view);

		mouse_sprite.setPosition(window.mapPixelToCoords(mouse.getPosition(window)));
			
		break;
	}

	default:
		break;
	}

	is_mouse_pressed = false;
}

void Game::render() {
	window.clear(sf::Color(34, 0, 92));

	level.get()->render(&window);
  
	for (auto& i : enemies) {
		i->render(&window);
	}

	player->render(&window);


	if (cur_weapon != nullptr)
	{
		cur_weapon->render(&window);
	}

	if (cur_game_state == GameState::moving) {
		counter.render(&window, sf::Vector2f(window.getView().getCenter().x,window.getView().getCenter().y - window.getSize().y / 2 + 30.0f));
	}

	ui.renderMain(&window,  sf::Vector2f(window.getView().getCenter().x - window.getSize().x / 2,window.getView().getCenter().y - window.getSize().y / 2));
	
	if(cur_game_state == GameState::action_menu || cur_game_state == GameState::weapons_list) {
		ui.renderList(&window);
	}

	window.draw(mouse_sprite);

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
		collisionYCorrection(ent, col[3], col[1], cur_pos.y, col_pos.y);
		return;
	}
	else if (col[0] != 0 && col[2] != 0) {
		collisionXCorrection(ent, col[0], col[2], cur_pos.x, col_pos.x);
		return;
	}

	bool prioritise_y_correction = (prev_pos.x < col_pos.x && (col[0] == 1 || col[2] == 1)) || (prev_pos.x + game_scale * sprite_dimensions > col_pos.x && (col[0] == -1|| col[2] == -1));

	if (prioritise_y_correction) {
		collisionYCorrection(ent, col[3], col[1], cur_pos.y, col_pos.y);
	}
	else {
		collisionXCorrection(ent, col[0], col[2], cur_pos.x, col_pos.x);
	}

	cur_pos = ent->getPosition();

	if (col[1] != 0 && cur_pos.x + game_scale * sprite_dimensions > col_pos.x || col[3] != 0 && cur_pos.x < col_pos.x ) {
		collisionYCorrection(ent, col[3], col[1], cur_pos.y, col_pos.y);
	}
	else if (col[0] != 0 && cur_pos.y + game_scale * sprite_dimensions > col_pos.y || col[2] != 0 && cur_pos.y < col_pos.y ) {
		collisionXCorrection(ent, col[0], col[2], cur_pos.x, col_pos.x);
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

void Game::gameExit() {
	std::cout << "Exiting game..." << std::endl;

	cur_game_state = GameState::not_running;
}

void Game::collisionYCorrection(Entity *ent, int left_col_dir, int right_col_dir, float ent_y, float col_y) {
	int dir = left_col_dir == 0 ? right_col_dir : left_col_dir;
	if (dir == -1)
	{
		ent->setGrounded(true);
	}

	float offset = dir == 1 ? (col_y - ent_y) : (col_y - ent_y) - game_scale * sprite_dimensions;

	ent->setVelocity(sf::Vector2f(ent->getVelocity().x, 0.0f));
	ent->move(sf::Vector2f(0.0f, offset));
}

void Game::collisionXCorrection(Entity *ent, int top_col_dir, int bottom_col_dir, float ent_x, float col_x) {
	int dir = top_col_dir == 0 ? bottom_col_dir : top_col_dir;
	
	float offset = dir == 1 ? (col_x - ent_x) : (col_x - ent_x) - game_scale * sprite_dimensions;

	ent->setVelocity(sf::Vector2f(0.0f, ent->getVelocity().y));
	ent->move(sf::Vector2f(offset, 0.0f));
}

void Game::weaponCollisions() {

	std::vector<sf::Sprite>* weapon_sprites = cur_weapon->getSpritesForCollision();

	for (int i = 0; i < weapon_sprites->size(); i++) {
		if (!cur_weapon->isActive(i)) {
			continue;
		}

		float angle = weapon_sprites->at(i).getRotation() * 3.14 / 180;

		std::vector<sf::Vector2f> collision_points;

		// using x' = xcos(theta) - ysin(theta), y' = ycos(theta) + xsin(theta)
		float right_relative_to_origin = weapon_sprites->at(i).getTextureRect().width * game_scale / 2;
		sf::Vector2f right_rotated(right_relative_to_origin * cos(angle), right_relative_to_origin * sin(angle));

		float bottom_relative_to_origin = weapon_sprites->at(i).getTextureRect().height * game_scale / 2;
		sf::Vector2f bottom_rotated( - bottom_relative_to_origin * sin(angle), bottom_relative_to_origin * cos(angle));

		collision_points.push_back(right_rotated + weapon_sprites->at(i).getPosition());
		collision_points.push_back(-right_rotated + weapon_sprites->at(i).getPosition());
		collision_points.push_back(bottom_rotated + weapon_sprites->at(i).getPosition());
		collision_points.push_back(-bottom_rotated + weapon_sprites->at(i).getPosition());

		collision_points.push_back(right_rotated + bottom_rotated + weapon_sprites->at(i).getPosition());
		collision_points.push_back( - right_rotated - bottom_rotated + weapon_sprites->at(i).getPosition());
		collision_points.push_back(right_rotated - bottom_rotated + weapon_sprites->at(i).getPosition());
		collision_points.push_back(- right_rotated + bottom_rotated + weapon_sprites->at(i).getPosition());

		for (auto& e : enemies) {
			sf::IntRect hitbox = e->getHitbox();
			for (int t = 0; t < 8; t++) {
				if (hitbox.contains((int)collision_points[t].x, (int)collision_points[t].y)) {
					std::cout << "Weapon hit an enemy!" << std::endl;
					e->takeDamage(cur_weapon->getDamage());
					cur_weapon->setInactive(i);
					break;
				}
			}
		}

		for (int t = 0; t < 8; t++) {
			if (collision_points[t].x < 0 || collision_points[t].y >= level.get()->getLevelDim().y * game_scale * sprite_dimensions 
				|| collision_points[t].x >= level.get()->getLevelDim().x * game_scale * sprite_dimensions) {
				std::cout << "Weapon is out of the map boundry!" << std::endl;
				cur_weapon->setInactive(i);
				break;
			}

			sf::Vector2i collision_to_grid(collision_points[t].x / (game_scale * sprite_dimensions), 
				collision_points[t].y / (game_scale * sprite_dimensions));

			if (level.get()->getTileType(collision_to_grid)) {
				std::cout << "Weapon hit a solid tile!" << std::endl;
				cur_weapon->setInactive(i);
				break;
			}
		}
	}

	int old_size = enemies.size();

	enemies.erase(std::remove_if(enemies.begin(), enemies.end(), 
		[](const Enemy* en){ return en->getHealth() <= 0; }), enemies.end());
	
	if (old_size != enemies.size()) {
		std::cout << old_size - enemies.size() << " enemy(ies) was defeated!" << std::endl;
	}
}

void Game::shuffleEnemies()
{
    std::vector<sf::Vector2i> spawns;
	spawns.push_back(sf::Vector2i(player->getPosition().x / (game_scale * sprite_dimensions), player->getPosition().y / (game_scale * sprite_dimensions)));

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

	mouse_sprite.setPosition(window.mapPixelToCoords(mouse.getPosition(window)));
}