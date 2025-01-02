#ifndef GAMEUI_H
#define GAMEUI_H

#include "List.h"
#include "NumDisplay.h"

#include "SFML/Graphics.hpp"

#include <iostream>
#include <string>
#include <vector>

class GameUI {
private:
    const int* player_health = nullptr;
    const int* num_arrows = nullptr;
    const int* coins = nullptr;

	sf::Texture heart_tex;
	sf::Sprite heart_sprite;
    sf::IntRect heart_texture_rect;
	sf::Texture arrow_tex;
	sf::Sprite arrow_sprite;

    NumDisplay coin_counter;

    List list;

public:
    GameUI() = default;                                         // Default Constructor
    GameUI(const int* player_health, const int* num_arrows, const int* coins);    // Dafult constructor which takes pointers to player stats for displaying on screen
    void setSprites(float game_scale);                          // Sets the properties of sprites
    void makeList(std::vector<std::string> new_list, const sf::Vector2f new_position); // Creates a new list of strings to be displayed
    int update(sf::Vector2f mouse_pos);                         // Uses the mouse position to determine which (if any) button in the list is being hovered over
    void renderMain(sf::RenderWindow* win, sf::Vector2f view_centre); // Renders UI elements that should alomst always be on screen, such as health and ammo
    void renderList(sf::RenderWindow* win);                     // Renders the list and background rectangles
    bool isListEmpty();                                         // Returns whether or not the list has no elements in it
    void resetList();                                           // Clears the content of the list
};

#endif