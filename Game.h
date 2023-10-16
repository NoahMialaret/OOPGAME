#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"

#include "Counter.h"
#include "Enemy.h"
#include "Entity.h"
#include "GameUI.h"
#include "Level.h"
#include "NPC.h"
#include "Player.h"
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

//Game object handles most of the game proccesses and is responsible for updating and rendering
class Game {
public:
	enum class GameState {
		not_running,
		title,
		starting_play,
		action_menu,
		moving,
		weapons_list,
		attacking,
		level_viewer,
		enemy_turn,
		challenge_mode
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

	std::vector<std::string> main_ui_list;
	
	//Game Objects ----------------------------------------------------- 
	std::unique_ptr<Level> level = nullptr;
  
	Player* player;

	Weapon* cur_weapon = nullptr;

	std::vector<Enemy*> enemies;


	Counter counter;

	GameUI ui;


public:
	Game() = delete;
	Game(const char* title); //Game constructor

	//Basic gmae loop functions
	void handleEvents();	 //Handles SFML events
	void update(sf::Clock& clock);			 //Handles game logic
	void render();			 //Handles graphics rendering

	void handleCollision(Entity* ent, sf::Vector2f prev_pos);

	void clean();			 //Destroys and cleans multiple proccesses upon termination

	Game::GameState getCurGameState() const; //Returns isRunning

private:
	void gameExit();

	void collisionYCorrection(Entity* ent, int left_col_dir, int right_col_dir, float ent_y, float col_y);
	void collisionXCorrection(Entity* ent, int top_col_dir, int bottom_col_dir, float ent_x, float col_x);
	void weaponCollisions();
	void shuffleEnemies(sf::Clock& clock);
	void updateMainView();
};

#endif