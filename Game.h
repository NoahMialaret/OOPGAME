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

	//Game Objects -----------------------------------------------------

	//Game Variables ----------------------------------------------------
	GameState cur_game_state = GameState::not_running; // The current state of the game

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