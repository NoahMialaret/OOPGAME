#ifndef ENTITY_H
#define ENTITY_H

#include <algorithm>
#include <iostream>

#include "SFML/Graphics.hpp"

class Entity {
protected:
	sf::Texture tex;
	sf::Sprite sprite;

	sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f); // Vector representing the players velocity

	bool can_increase_jump_velocity = false; // Determines whether holding the jump button will continue adding height (can't think of a better name...)
	bool jump_hold = false; // Shows whether the jump button has been held after performing a jump 

    bool is_grounded = false;	 // Boolean representing whether the character is grounded and can jump

public:
    Entity(const char* tex_name, float game_scale);
    void update(const sf::RenderWindow* win, bool jump_button, bool left_button, bool right_button);
    void render(sf::RenderWindow* win) const;
};

#endif