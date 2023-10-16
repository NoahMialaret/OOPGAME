#include <SFML/Graphics.hpp>

#include "Game.h"

Game game("Jumperboiii");

int main()
{
    sf::Clock clock;

	//creating the play button:
	sf::Texture play_button_tex;
	if(!play_button_tex.loadFromFile("art/playButton.png")) {
		std::cout << "play button texture couldn't load" << std::endl;
	}
	Button play_button(&play_button_tex, 400, 300);

	//white texture and text added to the shop button just for debugging, delete when an actual Shop button is designed
	Texture white;
    if (!white.loadFromFile("art/whiteImageForTesting.png", sf::IntRect(0, 0, 50, 20)))
    {
        std::cout << "white texture couldnt load" << std::endl;
    };
    Font dogicapixel;
    if (!dogicapixel.loadFromFile("files/dogicapixel.ttf")) {
        std::cout << "dogicapixel font couldn't load" << std::endl;
    }
    Text shop_button_text; shop_button_text.setString("Shop"); shop_button_text.setFont(dogicapixel); shop_button_text.setCharacterSize(30); shop_button_text.setFillColor(Color::Blue); shop_button_text.setPosition(230,120);

    Button shop_button(&white,200,100);

	switch (game.mainMenu(&play_button, &shop_button, &shop_button_text)) {
		case 1:
			//Main game loop
			while (game.getCurGameState() != Game::GameState::not_running)
			{
				// put pause button in handleEvents method
				// if statement starting here that checks if current game state is pause
				// if condition true
				float nextFrameStart = (float)clock.getElapsedTime().asMilliseconds() + (1000.0f / 60.0f);


	    	game.handleEvents();
		    game.update(clock);
		    game.render();
        

				while ((float)clock.getElapsedTime().asMilliseconds() < nextFrameStart);
			}

			break;

		case 2:
				game.shop();
				break;
	}

	

	

	//Cleans game after it has stopped running
	game.clean();

	return 0;
}