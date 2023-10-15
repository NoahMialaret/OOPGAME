#ifndef GAMEUI_H
#define GAMEUI_H

#include "SFML/Graphics.hpp"

#include <iostream>
#include <string>
#include <vector>

class GameUI {
private:
    const int* player_health = nullptr;
    const int* num_arrows = nullptr;

	sf::Texture heart_tex;
	sf::Sprite heart_sprite;
    sf::IntRect heart_texture_rect;
	sf::Texture arrow_tex;
	sf::Sprite arrow_sprite;

    std::vector<std::string> list;
    sf::Font font;
    sf::Text text;
    sf::Vector2f list_position;
    sf::RectangleShape list_background_rect;

    int highlight_index = 0;
    int clicked_index = 0;
public:
    GameUI() = default;
    GameUI(const int* player_health, const int* num_arrows);
    void setSprites(float game_scale);
    void makeList(std::vector<std::string> new_list, const sf::Vector2f new_position);
    int update(sf::Vector2f mouse_pos);
    void renderMain(sf::RenderWindow* win, sf::Vector2f view_centre);
    void renderList(sf::RenderWindow* win);
    bool isListEmpty();
    void resetList();
};

#endif