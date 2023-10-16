#ifndef BOW_H
#define BOW_H

#include "SFML/Graphics.hpp"

#include "Weapon.h"

class Bow : public Weapon {
protected:
    float intial_arrow_speed = 0.0f;
    sf::Sprite bow_sprite;
    sf::Texture bow_texture;
    std::vector<sf::Vector2f> arrow_velocities;
public:
    Bow(float speed, int damage, int gold_cost, std::string name, float game_scale);
    void updateWeapon(sf::Vector2f mouse_pos) override;
    void render(sf::RenderWindow* win) override;
};

#endif