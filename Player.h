#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

#include <algorithm>
#include <iostream>

#include "SFML/Graphics.hpp"

class Player : public Entity {
protected:
	bool can_increase_jump_velocity = false; // Determines whether holding the jump button will continue adding height (can't think of a better name...)
	bool jump_hold = false; // Shows whether the jump button has been held after performing a jump 

    int health = 5;
public:
    Player(const char* tex_name, float game_scale, sf::Vector2f pos);
    void update(const sf::RenderWindow* win, bool jump_button, bool left_button, bool right_button);
    void setVelocity(sf::Vector2f new_vel) override;
};

#endif