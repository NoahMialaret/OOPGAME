# To execute, run: make <section_name> in the terminal. e.g: make game_run

# Makes an executable
game: main.cpp Game.cpp
	@g++ -std=c++20 main.cpp Game.cpp Entity.cpp Player.cpp Enemy.cpp NPC.cpp Tile.cpp Level.cpp Dialogue.cpp -o OOPGame -lsfml-graphics -lsfml-window -lsfml-system

# Makes and runs an executable
game_run: main.cpp Game.cpp
	@make game
	@./OOPGame