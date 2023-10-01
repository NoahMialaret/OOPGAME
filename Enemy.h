#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

#include <algorithm>
#include <iostream>
#include <random>

#include "SFML/Graphics.hpp"

class Enemy : public Entity {
private:
    std::mt19937 rng;

    int health = 3;
public:
    Enemy(const char* tex_name, float game_scale, sf::Vector2u level_bounds);
    //void attack();
    sf::Vector2f teleport(const sf::Vector2u& level_bounds);
};

#endif