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
    std::vector<std::string> list;
    std::vector<std::string> sub_list;

	sf::Texture heart_tex;
	sf::Sprite heart_sprite;
    sf::IntRect heart_texture_rect;
	sf::Texture arrow_tex;
	sf::Sprite arrow_sprite;

    sf::Font font;
    sf::Text text;
    sf::Vector2f position;
public:
    GameUI() = default;
    GameUI(const int* player_health, const int* num_arrows);
    void setSprites(float game_scale);
    void makeList(std::vector<std::string> list);
    void makeSubList(std::vector<std::string> sub_list);
    int update(sf::Vector2f mouse_pos);
    void render(sf::RenderWindow* win, sf::Vector2f view_centre);
};

#endif