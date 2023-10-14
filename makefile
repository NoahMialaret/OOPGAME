# To execute, run: make <section_name> in the terminal. e.g: make game_run

# Makes an executable
game:
	@g++ -std=c++20 main.cpp Game.cpp Entity.cpp Player.cpp Enemy.cpp NPC.cpp Tile.cpp Level.cpp Weapon.cpp Bow.cpp BasicBow.cpp MultiBow.cpp CrossBow.cpp Melee.cpp BroardSword.cpp Daggers.cpp -o Jumperboiii -lsfml-graphics -lsfml-window -lsfml-system

# Makes and runs an executable
game_run:
	@make game
	@./Jumperboiii

# Runs the game output
run:
	@./Jumperboiii