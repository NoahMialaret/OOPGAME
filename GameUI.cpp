#include "GameUI.h"

GameUI::GameUI(const int* player_health, const int* num_arrows, const int* coins)
    :
    player_health(player_health),
    num_arrows(num_arrows),
    coins(coins),
    coin_counter(*coins),
    list()
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

    coin_counter.setSprite(game_scale / 2);

    list.setText(game_scale);
}

void GameUI::makeList(std::vector<std::string> new_list, const sf::Vector2f new_position) {
    list.makeList(new_list, new_position);
}

int GameUI::update(sf::Vector2f mouse_pos) {    
    return list.update(mouse_pos);
}

void GameUI::renderMain(sf::RenderWindow* win, sf::Vector2f view_top_left) {

    if (coin_counter.GetNumber() != *coins) {
        coin_counter.SetNumber(*coins);
    }

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

    coin_counter.render(win, view_top_left + sf::Vector2f(10.0f, 90.0f));
}

void GameUI::renderList(sf::RenderWindow* win) {
    list.render(win);
}

bool GameUI::isListEmpty() {
    return list.isListEmpty();
}

void GameUI::resetList() {
    list.resetList();
}
