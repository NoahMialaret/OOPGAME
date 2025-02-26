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
    int max_arrows = 10;

    int coins = 100;

    bool is_attack_active = false;

    sf::Vector2f saved_position;

    std::vector<Weapon*> weapons;

    bool is_invincible = false;
    int invincibilty_start_time = 0;

    bool can_control = false;
public:
    Player(const char* tex_name, float game_scale);
    void update(bool jump_button, bool left_button, bool right_button, sf::Clock* clock);
    void render(sf::RenderWindow* win) const override;
    void setVelocity(sf::Vector2f new_vel) override;
    void reset();

    void giveWeapon(Weapon* weapon);
    Weapon* getWeapon(int index);
    std::vector<std::string> getWeaponNames();
    void clean();
    bool isAttackActive();
    void savePosition();

    const int* getHealth();
    bool takeDamage(int damage_amount, sf::Clock* clock);
    int* getArrows();
    bool addArrows(int amount);
    bool isStill();
    bool isInvincible() const;
    void setControl(bool control);
    bool addCoins(int amount);
    int* getCoins();
    bool hasWeapon(std::string weapon_name);
    bool heal();

    void setCoins(int amount);
    void setHealth(int amount);
    void setArrows(int amount);
};

#endif