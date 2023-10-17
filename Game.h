#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"

#include "Counter.h"
#include "Enemy.h"
#include "Entity.h"
#include "GameUI.h"
#include "Level.h"
#include "NPC.h"
#include "NumDisplay.h"
#include "Player.h"
#include "Shop.h"
#include "Tile.h"

#include "Weapon.h"
#include "Bow.h"
#include "BasicBow.h"
#include "MultiBow.h"
#include "CrossBow.h"
#include "BroardSword.h"
#include "Daggers.h"
#include "ShortSword.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "Button.h"

//Game object handles most of the game proccesses and is responsible for updating and rendering
class Game {
public:
	enum class GameState {
		not_running,
		title,
		paused,
		starting_play,
		action_menu,
		moving,
		weapons_list,
		attacking,
		level_viewer,
		enemy_turn,
		room_picker,
		challenge_wait,
		challenge_view,
		challenge_mode,
		shop,
		roullete
	};

private:
	//SFML Objects -----------------------------------------------------
    sf::RenderWindow window;

	sf::Texture mouse_tex;
	sf::Sprite mouse_sprite;

	sf::Mouse mouse;

	sf::View main_view;

	//Game Variables ---------------------------------------------------
	GameState cur_game_state = GameState::not_running; // The current state of the game
	GameState prev_game_state = GameState::not_running; // The previous state of the game, so that it can be returned to after leaving pause

    std::mt19937 rng;

	// Boolean values representing whether a particular button has been pressed
	bool is_d_pressed = false;
	bool is_a_pressed = false;
	bool is_w_pressed = false;
	bool is_s_pressed = false;
	bool is_space_pressed = false;
	bool is_escape_pressed = false;
	bool is_mouse_pressed = false;

	float game_scale = 4.0f;			// The scale which the game is rendered as
	float sprite_dimensions = 8.0f; 	// Assuming square sprites, could be changed to a vector for rectangular sprites

	bool has_moved = false;

	bool mouse_hold = false;

	bool dialogue_active = false;

	int next_enemy_attack_start = 0;
	int next_enemy_attack_index = 0;

	std::vector<std::string> main_ui_list;

	int cleared_rooms = -1;
	
	//Game Objects ----------------------------------------------------- 
	std::unique_ptr<Level> level = nullptr;
  
	Player* player = nullptr;

	NPC* npc = nullptr;

	Weapon* cur_weapon = nullptr;

	std::vector<Enemy*> enemies;

	Counter counter;

	GameUI ui;

	sf::Clock* clock;

	Shop* shop = nullptr;

public:
	Game() = delete;
	Game(const char* title, sf::Clock* clock); //Game constructor

	//Basic gmae loop functions
	void handleEvents();	 //Handles SFML events
	void update();			 //Handles game logic
	void render();			 //Handles graphics rendering

	void handleCollision(Entity* ent, sf::Vector2f prev_pos);

	void clean();			 //Destroys and cleans multiple proccesses upon termination

	Game::GameState getCurGameState() const; //Returns isRunning

	int mainMenu(Button* play_button, Button* shop_button);

private:
	void gameExit();

	void collisionYCorrection(Entity* ent, int left_col_dir, int right_col_dir, float ent_y, float col_y);
	void collisionXCorrection(Entity* ent, int top_col_dir, int bottom_col_dir, float ent_x, float col_x);
	void weaponCollisions();
	void EnemyCollisions();
	void shuffleEnemies();
	void updateMainView();
	void loadNewLevel();
};

#endif