#ifndef WEAPON_H
#define WEAPON_H

#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <cmath>

class Weapon {
protected:
    int damage = 0;
    int gold_cost = 0;
    std::vector<sf::Sprite> sprites;
    std::vector<bool> sprite_active;
    sf::Texture texture;
    std::string name;
    bool is_attacking = false;
    float game_scale = 1.0f;
public:
    Weapon(int damage, int gold_cost, std::string name, float game_scale);
    virtual void commenceAttack() = 0;
    virtual void updateWeapon(sf::Vector2f mouse_pos) = 0;
    virtual void updateAttack() = 0;
    virtual void render(sf::RenderWindow* win) = 0;
    virtual void reset() = 0;

    std::vector<sf::Sprite>* getSpritesForCollision();
    std::string getName();
    int getDamage() const;
    bool isAttacking();
    virtual void drawWeapon(sf::Vector2f centre_pos) = 0;
    float calculateAngle(sf::Vector2f mouse_pos, sf::Vector2f sprite_pos) const;
};

#endif