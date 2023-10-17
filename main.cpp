#include <SFML/Graphics.hpp>

#include "Game.h"


int main()
{
    sf::Clock clock;

	Game game("Jumperboiii", &clock);

	//creating the play button:
	sf::Texture play_button_tex;
	if(!play_button_tex.loadFromFile("art/NewGameButton.png")) {
		std::cout << "play button texture couldn't load" << std::endl;
	}
	Button play_button(&play_button_tex, 200,300);

	//white texture and text added to the shop button just for debugging, delete when an actual Shop button is designed
	Texture shop_button_tex;
    if (!shop_button_tex.loadFromFile("art/ShopButton.png"))
    {
        std::cout << "shop button texture couldnt load" << std::endl;
    };
    Button shop_button(&shop_button_tex,200,100);

	//credits button
	Texture credits_button_tex;
	if (!credits_button_tex.loadFromFile("art/CreditsButton.png")) {
		 std::cout << "creidts button texture couldnt load" << std::endl;
	}
	Button credits_button(&credits_button_tex,200,400);

	switch (game.mainMenu(&play_button, &shop_button, &credits_button)) {

		case 1:
			//Main game loop
			while (game.getCurGameState() != Game::GameState::not_running)
			{
				// put pause button in handleEvents method
				// if statement starting here that checks if current game state is pause
				// if condition true
				float nextFrameStart = (float)clock.getElapsedTime().asMilliseconds() + (1000.0f / 60.0f);

				game.handleEvents();
				game.update();
				game.render();

				while ((float)clock.getElapsedTime().asMilliseconds() < nextFrameStart);
			}
			break;

		case 2:
			//shop code here
			break;

		case 3:
			//credits code here
			std::cout << "User chose credits" << std::endl;
			break;


	}

	//Cleans game after it has stopped running
	game.clean();

	return 0;
}