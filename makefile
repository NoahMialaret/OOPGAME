# To execute, run: make <section_name> in the terminal. e.g: make game_run

# Makes an executable

game:
	@g++ -std=c++20 main.cpp Dialogue.cpp Game.cpp Entity.cpp Player.cpp Enemy.cpp NPC.cpp Tile.cpp Level.cpp Button.cpp Weapon.cpp Bow.cpp BasicBow.cpp MultiBow.cpp CrossBow.cpp Melee.cpp BroardSword.cpp Daggers.cpp ShortSword.cpp GameUI.cpp NumDisplay.cpp Counter.cpp List.cpp Shop.cpp -o Jumperboiii -lsfml-graphics -lsfml-window -lsfml-system

# Makes and runs an executable
game_run:
	@make game
	@./Jumperboiii

# Runs the game output
run:
	@./Jumperboiii