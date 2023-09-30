#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"

#include <algorithm>
#include <iostream>
#include <memory>

//Game object handles most of the game proccesses and is responsible for updating and rendering
class Game {
public:
	enum class GameState {
		not_running,
		title,
		settings,
		paused,
		standard_play,
	};

private:
	//SFML Objects -----------------------------------------------------
    sf::RenderWindow window;

	sf::Texture player_tex;
	sf::Sprite test_player;
	sf::Texture mouse_tex;
	sf::Sprite test_mouse;

	sf::Mouse mouse;

	//Game Objects -----------------------------------------------------
	sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f); // Vector representing the players velocity

	// Boolean values representing whether a particular button has been pressed
	bool is_d_pressed = false;
	bool is_a_pressed = false;
	bool is_space_pressed = false;

	bool can_increase_jump_velocity = false; // Determines whether holding the jump button will continue adding height (can't think of a better name...)
	bool jump_hold = false; // Shows whether the jump button has been held after performing a jump 

	float game_scale = 4.0f;			// The scale which the game is rendered as
	float sprite_dimensions = 8.0f; 	// Assuming square sprites, could be changed to a vector for rectangular sprites

	//Game Variables ----------------------------------------------------
	GameState cur_game_state = GameState::not_running; // The current state of the game

	bool is_grounded = false;	 // Boolean representing whether the character is grounded and can jump

public:
	Game() = delete;
	Game(const char* title); //Game constructor

	//Basic gmae loop functions
	void handleEvents();	 //Handles SFML events
	void update();			 //Handles game logic
	void render();			 //Handles graphics rendering

	void clean();			 //Destroys and cleans multiple proccesses upon termination

	Game::GameState getCurGameState() const; //Returns isRunning

private:
	void enableStandardPlay();
	void pause();
	void unpause();
	void gameExit();
};

#endif