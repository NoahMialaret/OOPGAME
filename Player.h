#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Weapon.h"
#include "Bow.h"
#include "BasicBow.h"

#include <algorithm>
#include <iostream>

#include "SFML/Graphics.hpp"

class Player : public Entity {
protected:
	bool can_increase_jump_velocity = false; // Determines whether holding the jump button will continue adding height (can't think of a better name...)
	bool jump_hold = false; // Shows whether the jump button has been held after performing a jump 

    int health = 5;

    std::vector<Weapon*> weapons;
    Weapon* cur_weapon = nullptr;
public:
    Player(const char* tex_name, float game_scale, sf::Vector2f pos);
    void update(const sf::RenderWindow* win, bool jump_button, bool left_button, bool right_button, sf::Vector2f mouse_pos);
    void render(sf::RenderWindow* win) const override;
    void setVelocity(sf::Vector2f new_vel) override;
    void reset();

    void giveWeapon(Weapon* weapon);
    void drawWeapon(int index);
    void putAwayWeapon();
    void clean();
};

#endif