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

    if (!font.loadFromFile("files/dogicapixel.ttf")) {
        std::cout << "Could not load the font for GameUI!" << std::endl;
    }
}

void GameUI::setSprites(float game_scale) {

	arrow_sprite.setTexture(arrow_tex, true);
	arrow_sprite.setScale(sf::Vector2f(game_scale, game_scale));

    heart_texture_rect = sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(8,8));

	heart_sprite.setTexture(heart_tex, true);
	heart_sprite.setScale(sf::Vector2f(game_scale, game_scale));
    heart_sprite.setTextureRect(heart_texture_rect);

    text.setFont(font);
    text.setCharacterSize(32);
    list_background_rect.setSize(sf::Vector2f(0.0f, 40.0f));
    list_background_rect.setFillColor(sf::Color::Black);
}

void GameUI::makeList(std::vector<std::string> new_list, const sf::Vector2f new_position) {
    list = new_list;

    float offset = 40.0f * list.size() - 4.0f;
    list_position = new_position + sf::Vector2f(0.0f, -offset);

    list_background_rect.setPosition(list_position.x, 0.0f);
}

int GameUI::update(sf::Vector2f mouse_pos)
{    
    list_background_rect.setPosition(list_position.x, list_position.y - 4.0f);

    for (int i = 0; i < list.size(); i++) {
        list_background_rect.setSize(sf::Vector2f(list[i].size() * text.getCharacterSize(), list_background_rect.getSize().y));

        sf::FloatRect f_rect(list_background_rect.getPosition(), list_background_rect.getSize());
        if (f_rect.contains(mouse_pos.x, mouse_pos.y)) {
            highlight_index = i;
            return highlight_index;
        }

        list_background_rect.move(0.0f, 40.0f);
    }
    highlight_index = -1;

    return -1;
}

void GameUI::renderMain(sf::RenderWindow* win, sf::Vector2f view_top_left) {
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

void GameUI::renderList(sf::RenderWindow* win) {
    text.setPosition(list_position);
    list_background_rect.setPosition(list_background_rect.getPosition().x, text.getPosition().y - 4.0f);

    for (int i = 0; i < list.size(); i++) {
        if (i == highlight_index) {
            list_background_rect.setFillColor(sf::Color::White);
            text.setFillColor(sf::Color::Black);
        }
        else {
            list_background_rect.setFillColor(sf::Color::Black);
            text.setFillColor(sf::Color::White);
        }
        text.setString(list[i]);
        list_background_rect.setSize(sf::Vector2f(list[i].size() * text.getCharacterSize(), list_background_rect.getSize().y));
        win->draw(list_background_rect);
        win->draw(text);
        text.move(0.0f, 40.0f);
        list_background_rect.move(0.0f, 40.0f);
    }
}

bool GameUI::isListEmpty() {
    return list.empty();
}

void GameUI::resetList() {
    list.clear();
    list_position = sf::Vector2f(0.0f, 0.0f);
}
