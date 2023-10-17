#include "Game.h"

Game::Game(const char* title, sf::Clock* clock) 
	:
    rng(std::random_device()()),
	clock(clock)
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

	//creating the play button:
	if(!play_button_tex.loadFromFile("art/NewGameButton.png")) {
		std::cout << "play button texture couldn't load" << std::endl;
	}
	play_button = new Button(&play_button_tex, 200,200);

	//credits button
	if (!credits_button_tex.loadFromFile("art/CreditsButton.png")) {
		 std::cout << "creidts button texture couldnt load" << std::endl;
	}
	credits_button = new Button(&credits_button_tex,200,300);

    if (!close_button_tex.loadFromFile("art/CloseButton.png"))
    {
        std::cout << "close button texture couldnt load" << std::endl;
    };
    close_button = new Button(&close_button_tex,200,400);
	
    if (!shop_button_tex.loadFromFile("art/ShopButton.png"))
    {
        std::cout << "Shop button texture couldn't load" << std::endl;
    }
    shop_button = new Button(&shop_button_tex,200,100);

    if (!challenge_button_tex.loadFromFile("art/ChallengeButton.png"))
    {
        std::cout << "Challenge button texture couldn't load" << std::endl;
    }
    challenge_button = new Button(&challenge_button_tex,200,200);

    if (!roulette_button_tex.loadFromFile("art/RouletteButton.png"))
    {
        std::cout << "Roulette button texture couldn't load" << std::endl;
    }
    roulette_button = new Button(&roulette_button_tex,200,300);


	mouse_sprite.setTexture(mouse_tex, true);
	mouse_sprite.setScale(sf::Vector2f(game_scale, game_scale));

	std::cout << "Enabling Title play." << std::endl;
	cur_game_state = GameState::title;

	player = new Player("art/Player.png", game_scale);

	Weapon* shortsword = new ShortSword(game_scale);

	player->giveWeapon(shortsword);

	ui = GameUI(player->getHealth(), player->getArrows(), player->getCoins());
	ui.setSprites(game_scale);

	main_ui_list.push_back("Move");
	main_ui_list.push_back("Weapon");
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

			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button) {
					case sf::Mouse::Left:
						if (!mouse_hold) {
							is_left_mouse_pressed = true;
							mouse_hold = true;
						}
						break;
					case sf::Mouse::Right:
						if (!mouse_hold) {
							is_right_mouse_pressed = true;
							mouse_hold = true;
						}
						break;
				}
				break;
				
			case sf::Event::MouseButtonReleased:
				switch (event.mouseButton.button) {
					case sf::Mouse::Left:
					case sf::Mouse::Right:
						mouse_hold = false;
						break;
				}
				break;

			case sf::Event::KeyPressed:

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

					case sf::Keyboard::T:
						cur_game_state = GameState::title;
						main_view.setCenter(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
						window.setView(main_view);
						break;

					case sf::Keyboard::Space:
						is_space_pressed = true;
						break;

					case sf::Keyboard::Escape:
						is_escape_pressed = true;
						break;
				}
				break;
				
			case sf::Event::KeyReleased:

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

void Game::update() {

	if (cur_game_state == GameState::not_running) {
		return;
	}

	if (*player->getHealth() <= 0) {
		cur_game_state = GameState::title;
		std::cout << "Player is dead, returning to title!" << std::endl;
		return;
	}

	if (dialogue_active) {
		mouse_sprite.setPosition(window.mapPixelToCoords(mouse.getPosition(window)));
		if (is_left_mouse_pressed) {
			if (dialogue.readLine()) {
				dialogue_active = false;
			}
		}
		is_left_mouse_pressed = false;
		return;
	}


	if (enemies.size() == 0 && cur_game_state == GameState::action_menu) {
		std::cout << "All enemies have been defeated! Now pick your next room..." << std::endl;
		cur_game_state = GameState::room_picker;
		main_view.setCenter(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
		window.setView(main_view);
	}

	for (auto& e : enemies) {
		sf::Vector2f prev_pos = e->getPosition();
		if (cur_game_state != GameState::enemy_turn || e->isAttacking()) {
			e->update(clock);
		}
		if (cur_game_state != GameState::enemy_turn) {
			handleCollision(e, prev_pos);
		}
	}

	if (npc != nullptr) {
		sf::Vector2f prev_pos = npc->getPosition();
		npc->update();
		handleCollision(npc, prev_pos);
	}

	if (cur_game_state != GameState::title && cur_game_state != GameState::room_picker) {
		sf::Vector2f prev_pos = player->getPosition();

		player->update(is_space_pressed, is_a_pressed, is_d_pressed, clock);
		
		handleCollision(player, prev_pos);
		EnemyCollisions();

		if (player->getPosition().y > level.get()->getLevelDim().y * game_scale * sprite_dimensions) {
			std::cout << "Player fell into a pit! Reseting player." << std::endl;
			player->takeDamage(1, clock);
			player->reset();
			is_a_pressed = false;
			is_d_pressed = false;
			is_space_pressed = false;
		}
	}


	if (cur_game_state != GameState::level_viewer && cur_game_state != GameState::room_picker && cur_game_state != GameState::title) {
		updateMainView();
	}


	switch (cur_game_state) {
		case GameState::title:
			mainMenu();
			break;

		case GameState::starting_play:
			shuffleEnemies();
			cur_game_state = GameState::action_menu;
			break;

		case GameState::enemy_turn:
			updateEnemyTurn();
			break;
		
		case GameState::action_menu:
			updateActionMenu();
			break;

		case GameState::moving:
			updateMoving();
			break;

		case GameState::weapons_list:
			updateWeaponsList();
			break;

		case GameState::attacking:
			updateAttack();
			break;

		case GameState::level_viewer:
			updateLevelViewer();			
			break;

		case GameState::room_picker:
			updateRoomPicker();
			break;

		case GameState::shop:
			updateShop();
			break;

		case GameState::challenge_wait:
			updateChallengeWait();
			break;

		case GameState::challenge_mode:
			updateChallengeMode();
			break;

		case GameState::roullete: 
			updateRoulette();
			break;

		default:
			break;
	}

	is_left_mouse_pressed = false;
	is_right_mouse_pressed = false;
}

void Game::render() {
	if (cur_game_state == GameState::not_running) {
		return;
	}

	window.clear(sf::Color(34, 0, 92));

	if (cur_game_state == GameState::title) {
		play_button->draw(&window);
		close_button->draw(&window);
		credits_button->draw(&window);
		window.draw(mouse_sprite);
		if (dialogue_active) {
			dialogue.render(&window);
		}
		window.display();	
		return;
	}

	if (cur_game_state != GameState::title && cur_game_state != GameState::room_picker) {
		level.get()->render(&window);
		player->render(&window);
		for (auto& e : enemies) {
			if (cur_game_state != GameState::enemy_turn || e->isAttacking()) {
				e->render(&window);
			}
		}
	}

	if (npc != nullptr) {
 		npc->render(&window);
	}

	if (cur_weapon != nullptr)
	{
		cur_weapon->render(&window);
	}

	if (cur_game_state == GameState::moving || cur_game_state == GameState::challenge_mode) {
		counter.render(&window, sf::Vector2f(window.getView().getCenter().x,window.getView().getCenter().y - window.getSize().y / 2 + 30.0f));
	}

	ui.renderMain(&window,  sf::Vector2f(window.getView().getCenter().x - window.getSize().x / 2,window.getView().getCenter().y - window.getSize().y / 2));
	
	if(cur_game_state == GameState::action_menu || cur_game_state == GameState::weapons_list 
		|| cur_game_state == GameState::challenge_wait) {
		ui.renderList(&window);
	}

	if (cur_game_state == GameState::roullete) {
		// renderRoulette
	}

	if (cur_game_state == GameState::shop && shop != nullptr) {
		ui.renderList(&window);
		shop->render(&window);
		}

	if (cur_game_state == GameState::room_picker) {
		shop_button->draw(&window);
		challenge_button->draw(&window);
		roulette_button->draw(&window);
	}

	if (dialogue_active) {
		dialogue.render(&window);
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

	delete npc;

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
		std::cout << old_size - enemies.size() << " enemy was defeated! Remaining enemies: " << enemies.size() << std::endl;
		player->addCoins((old_size - enemies.size()) * 3);
	}
}

void Game::EnemyCollisions() {
	
	sf::IntRect player_hitbox = player->getHitbox();

	for (auto& e : enemies) {
		if (cur_game_state == GameState::enemy_turn && !e->isAttacking()) {
			continue;
		}

		sf::IntRect hitbox = e->getHitbox();
		if (hitbox.intersects(player_hitbox)) {

			if (!player->isInvincible() || cur_game_state != GameState::enemy_turn) {
				sf::Vector2f knockback((player->getPosition().x - e->getPosition().x) / (game_scale), 
					(player->getPosition().y - e->getPosition().y) / (game_scale));
				if (knockback.x == 0.0f) {
					knockback.x = 0.5f;
				}
				player->setVelocity(knockback);
			}
			player->takeDamage(1, clock);
			break;
		}
	}
}

void Game::NPCChallengeCollision() {
	assert(cur_game_state == GameState::challenge_mode);

	if(player->getHitbox().intersects(npc->getHitbox())) {
		std::cout << "You reached the end of the challenge! Here's " << counter.GetNumber() << " coins!" << std::endl;
		dialogue.startDialogue("Victory", main_view.getCenter() - sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
		dialogue_active = true;
		player->addCoins(counter.GetNumber());
		player->setControl(false);
		loadNewLevel();
		cur_game_state = GameState::action_menu;
		ui.resetList();
		delete npc;
		npc = nullptr;
	}
}

void Game::shuffleEnemies()
{
    std::vector<sf::Vector2i> spawns;
	spawns.push_back(sf::Vector2i(player->getPosition().x / (game_scale * sprite_dimensions), player->getPosition().y / (game_scale * sprite_dimensions)));
	spawns.push_back(sf::Vector2i((player->getPosition().x + game_scale * sprite_dimensions) / (game_scale * sprite_dimensions), player->getPosition().y / (game_scale * sprite_dimensions)));

	for (auto& i : enemies) {
		sf::Vector2i spawn_grid_pos;
		bool can_spawn = false;

		int start_time = clock->getElapsedTime().asMilliseconds();

		while (!can_spawn && start_time + 100 > clock->getElapsedTime().asMilliseconds()) {
			can_spawn = true;
			spawn_grid_pos = level.get()->getValidSpawnPos(rng);

			for (int i = 0; i < spawns.size(); i++) {
				if (spawn_grid_pos == spawns[i]) {
					can_spawn = false;
					break;
				}
			}
		}
			
		if (!can_spawn) {
			std::cout << "Could not find a valid enemy spawn position in time! Removing enemy." << std::endl;
			i->takeDamage(999);
			enemies.erase(std::remove_if(enemies.begin(), enemies.end(), 
				[](const Enemy* en){ return en->getHealth() <= 0; }), enemies.end());
			continue;
		}

		spawns.push_back(spawn_grid_pos);
		sf::Vector2f spawn_pos(game_scale * sprite_dimensions * spawn_grid_pos.x, game_scale * sprite_dimensions * spawn_grid_pos.y);
		i->teleport(spawn_pos);
	}
}

void Game::updateMainView() {
	sf::Vector2f player_centre(player->getPosition().x + game_scale * sprite_dimensions / 2, player->getPosition().y + game_scale * sprite_dimensions / 2);
	main_view.setCenter(player_centre);

	if(main_view.getCenter().y + main_view.getSize().y / 2 > (level.get()->getLevelDim().y + 1) * game_scale * sprite_dimensions) {
		main_view.setCenter(main_view.getCenter().x, ((level.get()->getLevelDim().y + 1) * game_scale * sprite_dimensions) - main_view.getSize().y / 2);
	}

	if(main_view.getCenter().x - main_view.getSize().x / 2 < 0) {
		main_view.setCenter(main_view.getSize().x / 2, main_view.getCenter().y);
	}
	else if (main_view.getCenter().x + main_view.getSize().x / 2 > level.get()->getLevelDim().x * game_scale * sprite_dimensions) {
		main_view.setCenter((level.get()->getLevelDim().x * game_scale * sprite_dimensions) - main_view.getSize().x / 2, main_view.getCenter().y);
	}
	window.setView(main_view);

	mouse_sprite.setPosition(window.mapPixelToCoords(mouse.getPosition(window)));
}

void Game::loadNewLevel() {
	cleared_rooms++;
	std::cout << "loading new level! You have cleared " << cleared_rooms << " levels." << std::endl;
  	level = std::make_unique<Level>("level_1.txt", game_scale, sprite_dimensions);
	
	sf::Vector2i new_grid_pos = level.get()->getValidSpawnPos(rng);
	sf::Vector2f new_pos(game_scale * sprite_dimensions * new_grid_pos.x, game_scale * sprite_dimensions * new_grid_pos.y);

	player->setPosition(new_pos);
	player->setVelocity(sf::Vector2f(0.0f, 0.0f));

	for (int i = 0; i < 1; i++)	{
		enemies.push_back(new Enemy("art/Enemy.png", game_scale));
	}

	shuffleEnemies();
}

void Game::loadChallenge() {
	std::cout << "loading the challenge level!" << std::endl;
  	level = std::make_unique<Level>("challenge_1.txt", game_scale, sprite_dimensions);
	
	player->setPosition(sf::Vector2f(10.0f, (level.get()->getLevelDim().y - 2) * game_scale * sprite_dimensions));

	npc = new NPC("art/NPC.png", 4.0f, sf::Vector2f(game_scale * sprite_dimensions * 84, game_scale * sprite_dimensions * 9), "ChallengeMaster");
}

void Game::updateActionMenu() {
	if (ui.isListEmpty() && player->isStill()) {
		sf::Vector2f list_position = sf::Vector2f(window.getView().getCenter().x - window.getSize().x / 2, window.getView().getCenter().y + window.getSize().y / 2);
		ui.makeList(main_ui_list, list_position);
		is_left_mouse_pressed = false;
		return;
	}

	int list_index = ui.update(mouse_sprite.getPosition());

	if (is_right_mouse_pressed && list_index != -1) {
		dialogue.startDialogue(main_ui_list[list_index], main_view.getCenter() - sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
		dialogue_active = true;
	}

	if (!is_left_mouse_pressed) {
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
			player->savePosition();

			counter = Counter(clock, 5);
			counter.setSprite(game_scale);
			ui.resetList();
			player->setControl(true);
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

	case 2: // View Level
		std::cout << "Entering level viewer..." << std::endl;
		prev_game_state = cur_game_state;
		cur_game_state = GameState::level_viewer;
		break;

	case 3: // End Turn
		std::cout << "Ending turn..." << std::endl;
		cur_game_state = GameState::enemy_turn;
		next_enemy_attack_start = clock->getElapsedTime().asMilliseconds();
		next_enemy_attack_index = 0;
		ui.resetList();
		player->setControl(true);
		break;
	
	default:
		break;
	}
}

void Game::updateMoving() {
	if(is_escape_pressed || counter.update(clock)) {
		cur_game_state = GameState::action_menu;
		has_moved = true;
		player->setControl(false);
	}
}

void Game::updateWeaponsList() {
	if (is_escape_pressed) {
		ui.resetList();
		cur_game_state = GameState::action_menu;
		return;
	}
	int list_index = ui.update(mouse_sprite.getPosition());

	if (is_left_mouse_pressed && list_index != -1) {
		cur_weapon = player->getWeapon(list_index);
		cur_game_state = GameState::attacking;
	}
	else if (is_right_mouse_pressed && list_index != -1) {
		dialogue.startDialogue(player->getWeapon(list_index)->getName(), main_view.getCenter() - sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
		dialogue_active = true;
	}
}

void Game::updateAttack() {
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
		if (is_left_mouse_pressed) {
			cur_weapon->commenceAttack();
		}
	}
	else { // Weapon is attacking
		if (cur_weapon->updateAttack()) {
			cur_weapon->reset();
			cur_weapon = nullptr;
			ui.resetList();
			cur_game_state = GameState::enemy_turn;
			next_enemy_attack_start = clock->getElapsedTime().asMilliseconds();
			next_enemy_attack_index = 0;
			player->setControl(true);
		}
		else {
			weaponCollisions();
		}
	}
}

void Game::updateEnemyTurn()
{
    if (next_enemy_attack_start + 1000 < clock->getElapsedTime().asMilliseconds() && next_enemy_attack_index < enemies.size()) {
		
			std::uniform_int_distribution<int> x_dist(-1, 1);
			std::uniform_int_distribution<int> y_dist(-1, 1);

			int x_dir = 0;
			int y_dir = 0;
			
			// Stops enemies from spawning where the player is
			while(x_dir == 0 && y_dir == 0) {
				x_dir = x_dist(rng);
				y_dir = y_dist(rng);
			}

			float modifier = 1.0f;
			if (x_dir != 0 && y_dir != 0) {
				modifier = 0.75f;
			}
		
		enemies[next_enemy_attack_index]->startAttack(player->getPosition() + sf::Vector2f(x_dir * 600.0f * modifier, y_dir * 600.0f * modifier), 
			sf::Vector2f( - x_dir * 12.0f * modifier, - y_dir * 12.0f * modifier), clock);
			next_enemy_attack_index++;
			next_enemy_attack_start += 1000;
	}

	if(next_enemy_attack_index == enemies.size()) {

		bool is_attack_finished = true;

		for (auto& e : enemies) {
			if (e->isAttacking()) {
				is_attack_finished = false;
				break;
			}
		}

		if (is_attack_finished) {
			player->setControl(false);
			if (player->isStill()) {
				shuffleEnemies();
				has_moved = false;
				cur_game_state = GameState::action_menu;
			}
		}
	}
}

void Game::updateRoomPicker() {
	mouse_sprite.setPosition(window.mapPixelToCoords(mouse.getPosition(window)));
	if (!is_left_mouse_pressed) {
		return;
	}

	if (shop_button->checkClicked(sf::Mouse::getPosition(window))) {
		std::cout << "Shop button pressed!" << std::endl;
		cur_game_state = GameState::shop;
		level = std::make_unique<Level>("shop.txt", game_scale, sprite_dimensions);
		npc = new NPC("art/NPC.png", 4.0f, sf::Vector2f(600.0f, 400.0f), "Shopkeeper");
		player->setPosition(sf::Vector2f(200.0f, 400.0f));
		ui.resetList();
		dialogue.startDialogue("Shopkeeper", main_view.getCenter() - sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
		dialogue_active = true;
	}

	else if (challenge_button->checkClicked(sf::Mouse::getPosition(window))) {
		std::cout << "Challenge button pressed!" << std::endl;
		cur_game_state = GameState::challenge_wait;
		loadChallenge();
		ui.resetList();
		dialogue.startDialogue("Challenge", main_view.getCenter() - sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
		dialogue_active = true;
	}

	else if (roulette_button->checkClicked(sf::Mouse::getPosition(window))) {
		std::cout << "Roulette button pressed! (Not implemented)" << std::endl;
		dialogue.startDialogue("Roulette", main_view.getCenter() - sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
		dialogue_active = true;
	}
}

void Game::updateShop()
{
    if (ui.isListEmpty() && player->isStill()) {
		std::cout << "starting shop" << std::endl;
		sf::Vector2f list_position = sf::Vector2f(window.getView().getCenter().x - window.getSize().x / 2, window.getView().getCenter().y + window.getSize().y / 2);
		std::vector<std::string> shop_list = {"Exit shop"};
		ui.makeList(shop_list, list_position);
		is_left_mouse_pressed = false;
		shop = new Shop(rng, player, player->getArrows(), game_scale);
		return;
	}

	if (shop == nullptr) {
		return;
	}

	shop->update(mouse_sprite.getPosition(), &dialogue, &dialogue_active, is_left_mouse_pressed, is_right_mouse_pressed);

	int list_index = ui.update(mouse_sprite.getPosition());

	if (!is_left_mouse_pressed) {
		return;
	}

	switch (list_index)
	{
	case -1: // Nothing
		std::cout << "Nothing was pressed..." << std::endl;
		break;

	case 0: // Exit
		std::cout << "Exiting Shop." << std::endl;
		ui.resetList();
		loadNewLevel();
		cur_game_state = GameState::action_menu;
		delete npc;
		npc = nullptr;
		delete shop;
		shop = nullptr;
		break;
	
	default:
		break;
	}
}

void Game::updateChallengeWait() {
	if (ui.isListEmpty() && player->isStill()) {
		sf::Vector2f list_position = sf::Vector2f(window.getView().getCenter().x - window.getSize().x / 2, window.getView().getCenter().y + window.getSize().y / 2);
		std::vector<std::string> challenge_list = {"GO!", "View Level", "Exit"};
		ui.makeList(challenge_list, list_position);
		is_left_mouse_pressed = false;
		return;
	}

	int list_index = ui.update(mouse_sprite.getPosition());

	if (!is_left_mouse_pressed) {
		return;
	}

	switch (list_index)
	{
	case -1: // Nothing
		std::cout << "Nothing was pressed..." << std::endl;
		break;

	case 0: // GO!
		std::cout << "Good Luck!" << std::endl;
		cur_game_state = GameState::challenge_mode;
		counter = Counter(clock, 20);
		counter.setSprite(game_scale);
		player->setControl(true);
		break;

	case 1: // View Level
		std::cout << "Entering level viewer..." << std::endl;
		prev_game_state = cur_game_state;
		cur_game_state = GameState::level_viewer;
		break;

	case 2: // Exit
		std::cout << "Exiting Challenge." << std::endl;
		ui.resetList();
		loadNewLevel();
		cur_game_state = GameState::action_menu;
		break;
	
	default:
		break;
	}
}

void Game::updateChallengeMode() {
	if (counter.update(clock)) {
		std::cout << "You ran out of time! Better luck next time." << std::endl;
		dialogue.startDialogue("Fail", main_view.getCenter() - sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
		dialogue_active = true;
		player->setControl(false);
		loadNewLevel();
		cur_game_state = GameState::action_menu;
		delete npc;
		npc = nullptr;
		ui.resetList();
		return;
	}
	NPCChallengeCollision();
}

void Game::updateRoulette() {
	// Code for roulette's update function goes here
}

void Game::updateLevelViewer() {
	if (is_escape_pressed) {
		ui.resetList();
		cur_game_state = prev_game_state;
	}
	float speed = 8.0f;
	sf::Vector2f move( is_d_pressed * speed - is_a_pressed * speed, is_s_pressed * speed - is_w_pressed * speed);
	main_view.move(move);

	if(main_view.getCenter().y < 0.0f) {
		main_view.setCenter(main_view.getCenter().x, 0.0f);
	}
	else if (main_view.getCenter().y + main_view.getSize().y / 2 > (level.get()->getLevelDim().y + 1) * game_scale * sprite_dimensions) {
		main_view.setCenter(main_view.getCenter().x, ((level.get()->getLevelDim().y + 1) * game_scale * sprite_dimensions) - main_view.getSize().y / 2);
	}

	if(main_view.getCenter().x - main_view.getSize().x / 2 < 0.0f) {
		main_view.setCenter(main_view.getSize().x / 2, main_view.getCenter().y);
	}
	else if (main_view.getCenter().x + main_view.getSize().x / 2 > level.get()->getLevelDim().x * game_scale * sprite_dimensions) {
		main_view.setCenter((level.get()->getLevelDim().x * game_scale * sprite_dimensions)- main_view.getSize().x / 2, main_view.getCenter().y);
	}
	
	window.setView(main_view);

	mouse_sprite.setPosition(window.mapPixelToCoords(mouse.getPosition(window)));
}

void Game::mainMenu() {
	
	mouse_sprite.setPosition(window.mapPixelToCoords(mouse.getPosition(window)));
	if (!is_left_mouse_pressed) {
		return;
	}

	if (play_button->checkClicked(sf::Mouse::getPosition(window))) {
		std::cout << "Starting the game!" << std::endl;
		cur_game_state = GameState::starting_play;
		loadNewLevel();
	}

	if (credits_button->checkClicked(sf::Mouse::getPosition(window))) {
		std::cout << "Showing credits!" << std::endl;
		dialogue.startDialogue("Credits", sf::Vector2f(0.0f, 0.0f));
		dialogue_active = true;
	}

	if (close_button->checkClicked(sf::Mouse::getPosition(window))) {
		std::cout << "Closing the game..." << std::endl;
		cur_game_state = GameState::not_running;
	}
}