#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

#include <iostream>
#include <random>

#include "SFML/Graphics.hpp"

class Enemy : public Entity {
private:
    int health = 1;
public:
    Enemy(const char* tex_name, float game_scale);
    //void attack();
    void teleport(sf::Vector2f new_pos);
    void takeDamage(int damage_amount);
    int getHealth() const;
};

#endif