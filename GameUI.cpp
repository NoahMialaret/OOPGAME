#include "GameUI.h"

GameUI::GameUI(const int *player_health, const int *num_arrows)
    :
    player_health(player_health),
    num_arrows(num_arrows)
{
    if (!arrow_tex.loadFromFile("art/Arrow.png")) {
		std::cout << "Arrow texture could not be loaded!" << std::endl;
	}

    if (!heart_tex.loadFromFile("art/Heart.png")) {
		std::cout << "Heart texture could not be loaded!" << std::endl;
	}
}

void GameUI::setSprites(float game_scale) {

	arrow_sprite.setTexture(arrow_tex, true);
	arrow_sprite.setScale(sf::Vector2f(game_scale, game_scale));

    heart_texture_rect = sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(8,8));

	heart_sprite.setTexture(heart_tex, true);
	heart_sprite.setScale(sf::Vector2f(game_scale, game_scale));
    heart_sprite.setTextureRect(heart_texture_rect);
}

void GameUI::render(sf::RenderWindow *win, sf::Vector2f view_top_left) {
    heart_texture_rect.left = 0;
    heart_sprite.setTextureRect(heart_texture_rect);
    heart_sprite.setPosition(view_top_left + sf::Vector2f(10.0f, 10.0f));
    for (int i = 0; i < 5; i++) {
        if (i >= *player_health) {
            heart_texture_rect.left = 8;
            heart_sprite.setTextureRect(heart_texture_rect);
        }
        win->draw(heart_sprite);
        heart_sprite.move((heart_texture_rect.width + 1) * heart_sprite.getScale().x, 0.0f);
    }

    arrow_sprite.setPosition(view_top_left + sf::Vector2f(10.0f, 20.0f + heart_texture_rect.height * heart_sprite.getScale().y));
    for (int i = 0; i < *num_arrows; i++) {
        
        win->draw(arrow_sprite);
        arrow_sprite.move((arrow_sprite.getTextureRect().width + 1) * arrow_sprite.getScale().x, 0.0f);
    }
}
