#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

#include <iostream>
#include <random>

#include "SFML/Graphics.hpp"

class Enemy : public Entity {
private:
    int health = 3;

    bool is_attacking = false;
    int attack_start_time = 0;
public:
    Enemy(const char* tex_name, float game_scale);
    void update(sf::Clock* clock);
    void teleport(sf::Vector2f new_pos);
    void takeDamage(int damage_amount);
    void startAttack(sf::Vector2f start_pos, sf::Vector2f new_velocity, sf::Clock* clock);
    int getHealth() const;
    bool isAttacking() const;
};

#endif