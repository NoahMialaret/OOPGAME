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
    int max_health = 5;
    int arrows = 5;

    bool is_attack_active = false;

    std::vector<Weapon*> weapons;
public:
    Player(const char* tex_name, float game_scale, sf::Vector2f pos);
    void update(bool jump_button, bool left_button, bool right_button);
    void update();
    void render(sf::RenderWindow* win) const override;
    void setVelocity(sf::Vector2f new_vel) override;
    void reset();

    void giveWeapon(Weapon* weapon);
    Weapon* getWeapon(int index);
    void putAwayWeapon();
    void clean();
    bool isAttackActive();

    const int* getHealth();
    bool takeDamage(int damage_amount);
    const int* getArrows();
    bool isStill();
};

#endif