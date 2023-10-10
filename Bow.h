#ifndef BOW_H
#define BOW_H

#include "SFML/Graphics.hpp"

#include "Weapon.h"

class Bow : public Weapon {
protected:
    float range = 0;
    sf::Sprite bow_sprite;
    sf::Texture bow_texture;
public:
    Bow(float range, int damage, int gold_cost, std::string name, float game_scale);
    void render(sf::RenderWindow* win) override;
    void drawWeapon(sf::Vector2f centre_pos) override;
};

#endif